#pragma once

#include <cstdint>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>
#include <memory>
#include "../logger.hpp"
#include "../personal/jq.hpp"
#include "../events/eventhandler.hpp"

const uint8_t MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> sig;


class Existent
{
    public:
        Existent(uint32_t newID);
        uint32_t GetID() const;
        bool Equals(Existent other) const;
        class Universe* thisUniverse;
        template <typename T, typename ...TArgs> void AddElement(TArgs&& ...args);
        template <typename T> void CeaseElement();
        template <typename T> bool ElementExists();
        template <typename T> T& GetElement();
        void Cease();
        void SetTag(std::string newTag);
        std::string GetTag();

    private:
        uint32_t ID;
        std::string tag;
        
};

struct Ilement
{
    protected:
        static uint32_t nextID;
};

template <typename T>
class Element : public Ilement
{
    public:
        static uint32_t GetID() 
        {
            static auto id = nextID++;
            return id; 
        }
};

class System
{
    public:
        System() = default;
        ~System() = default;
        void AddExistentToSystem(Existent existent);
        void RemoveExistentFromSystem(Existent existent);
        std::vector<Existent> GetSystemExistents() const;
        const sig& GetElementSig() const;
        
        template <typename T> void RequireElement();

    private:
        std::vector<Existent> existents;
        sig elementSig;
};

template <typename T>
void System::RequireElement()
{
    const auto elementID = Element<T>::GetID();
    elementSig.set(elementID);
    
}

class IAssm 
{
    public:
        virtual ~IAssm() {}
};

template <typename T>
class Assembly : public IAssm
{
    public:
        Assembly(uint32_t size = 100) { Resize(size); }
        virtual ~Assembly() = default;

        bool IsEmpty() const { return data.empty(); }
        uint32_t GetSize() const { return data.size(); }
        void Resize(uint32_t size) { data.resize(size); }
        void Clear() { data.clear(); }
        void Add(T obj) { data.push_back(obj); }
        void Set(uint32_t idx, T obj) { data[idx] = obj; }
        T& Get(uint32_t idx) { return static_cast<T&>(data[idx]); }
        T& operator [](uint32_t idx) { return data[idx]; }
        
    private:
        std::vector<T> data;
};

class Universe
{
    public:
        Universe() = default;
        Existent CreateExistent();
        void CeaseExistent(Existent existent);
        void AddExistentToSystems(Existent existent);
        void CeaseExistentFromSystems(Existent existent);
        template <typename T, typename ...TArgs> void AddElement(Existent existent, TArgs&& ...args);
        template <typename T> void CeaseElement(Existent existent);
        template <typename T> bool ElementExists(Existent existent);
        template <typename T> T& GetElement(Existent existent);
        template <typename T, typename ...TArgs> void AddSystem(TArgs&& ...args);
        template <typename T> void RemoveSystem();
        template <typename T> bool SystemExists();
        template <typename T> T& GetSystem();
        void Update();
        
    private:
        uint32_t totalExistents = -1;
        std::vector<std::shared_ptr<IAssm>> elementAssembly;
        //std::vector<IAssm*> elementAssembly;
        std::vector<sig> existentElementsigs;
        std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
        JQ<Existent> addExistentQueue;
        JQ<Existent> ceaseExistentQueue;
        JQ<uint32_t> freeids;
        
};

template <typename T, typename ...TArgs>
void Universe::AddElement(Existent existent, TArgs&& ...args)
{
    const auto elementID = Element<T>::GetID();
    const auto existentID = existent.GetID();

    if (elementID >= elementAssembly.size()) { elementAssembly.resize(elementID + 1, nullptr); }
    if (!elementAssembly[elementID])
    {
        std::shared_ptr<Assembly<T>> newElementAssembly = std::make_shared<Assembly<T>>();
        elementAssembly[elementID] = newElementAssembly;
    }
    
    std::shared_ptr<Assembly<T>> ElementAssm = std::static_pointer_cast<Assembly<T>>(elementAssembly[elementID]);
    if (existentID >= ElementAssm->GetSize()) { ElementAssm->Resize(totalExistents); }

    T newElement(std::forward<TArgs>(args)...);
    ElementAssm->Set(existentID, newElement);
    existentElementsigs[existentID].set(elementID);
    Logger::Log(LOG_INFO, "Element " + std::to_string(elementID) + " added to existent " + std::to_string(existentID));
}

template <typename T>
void Universe::CeaseElement(Existent existent)
{
    const auto elementID = Element<T>::GetID();
    const auto existentID = existent.GetID();
    existentElementsigs[existentID].set(elementID, false);
    Logger::Log(LOG_INFO, "Element " + std::to_string(elementID) + " was removed from existent " + std::to_string(existentID));
    
}

template <typename T>
bool Universe::ElementExists(Existent existent)
{
    const auto elementID = Element<T>::GetID();
    const auto existentID = existent.GetID();

    return existentElementsigs[existentID].test(elementID);
}

template <typename T>
T& Universe::GetElement(Existent existent)
{
    const auto elementID = Element<T>::GetID();
    const auto existentID = existent.GetID();
    auto elementAssm = std::static_pointer_cast<Assembly<T>>(elementAssembly[elementID]);
    return elementAssm->Get(existentID);
}

template <typename T, typename ...TArgs>
void Universe::AddSystem(TArgs&& ...args)
{
    std::shared_ptr<T> newSystem = std::make_shared<T>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(T)), newSystem));
}

template <typename T>
void Universe::RemoveSystem()
{
    auto system = systems.find(std::type_index(typeid(T)));
    systems.erase(system);
}

template <typename T>
bool Universe::SystemExists()
{
    return systems.find(std::type_index(typeid(T))) != systems.end();
}

template <typename T>
T& Universe::GetSystem()
{
    auto system = systems.find(std::type_index(typeid(T)));
    return *(std::static_pointer_cast<T>(system->second));
}

template <typename T, typename ...TArgs>
void Existent::AddElement(TArgs&& ...args)
{
    thisUniverse->AddElement<T>(*this, std::forward<TArgs>(args)...);
}

template <typename T>
void Existent::CeaseElement()
{
    thisUniverse->CeaseElement<T>(*this);
}

template <typename T>
bool Existent::ElementExists()
{
   return thisUniverse->ElementExists<T>(*this);
}

template <typename T>
T& Existent::GetElement()
{
    return thisUniverse->GetElement<T>(*this);
}
