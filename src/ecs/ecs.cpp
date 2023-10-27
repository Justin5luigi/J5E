#include "ecs.hpp"
#include <iostream>
#include <algorithm>

uint32_t Ilement::nextID = 0;

Existent::Existent(uint32_t newID) { ID = newID; }

uint32_t Existent::GetID() const { return ID; }

void Existent::SetTag(std::string newTag) { tag = newTag; }

std::string Existent::GetTag() { return tag; }

bool Existent::Equals(Existent other) const { return this->ID == other.GetID(); }

void System::AddExistentToSystem(Existent existent) { existents.push_back(existent); }
        
void System::RemoveExistentFromSystem(Existent existent)
{
    //existents.erase(std::remove_if(existents.begin(), existents.end(), [&existent](&existent other) { return existent.equals(other);}), existents.end());
    existents.erase(std::remove_if(existents.begin(), existents.end(), [&existent](Existent other) {
        return existent.Equals(other);
    }), existents.end());
}

std::vector<Existent> System::GetSystemExistents() const { return existents; }

const sig& System::GetElementSig() const { return elementSig; }

Existent Universe::CreateExistent()
{
    uint32_t newExistentID;
    if (freeids.IsEmpty()) 
    {
        totalExistents ++;
        newExistentID = totalExistents;
        if (newExistentID > existentElementsigs.size()) { existentElementsigs.resize(newExistentID + 1); }
    }
    
    else { newExistentID = freeids.Dequeue(); }
    
    Existent existent(newExistentID);
    existent.thisUniverse = this;
    addExistentQueue.Enqueue(existent);
    if (newExistentID >= existentElementsigs.size())
    {
        existentElementsigs.resize(newExistentID + 1);
    }
    Logger::Log(LOG_INFO, "Entity created with id = " + std::to_string(newExistentID));
    return existent;
}

void Universe::AddExistentToSystems(Existent existent)
{
    const auto existentID = existent.GetID();
    const auto& existentElementSig = existentElementsigs[existentID];

    for (auto& system : systems)
    {
        const auto& sysElementSig = system.second->GetElementSig();
        if ((existentElementSig & sysElementSig) == sysElementSig)
        {
            system.second->AddExistentToSystem(existent);
        } 
    }
}

void Universe::CeaseExistentFromSystems(Existent existent)
{
    for (auto system : systems) { system.second->RemoveExistentFromSystem(existent); }
}

void Universe::Update()
{
    while (!addExistentQueue.IsEmpty()) { AddExistentToSystems(addExistentQueue.Dequeue()); }
    while (!ceaseExistentQueue.IsEmpty()) 
    { 
        Existent existent = ceaseExistentQueue.Dequeue();
        CeaseExistentFromSystems(existent);
        existentElementsigs[existent.GetID()].reset();
        Logger::Log(LOG_INFO, "Existent " + std::to_string(existent.GetID()) + " ceases to exist.");
        freeids.Enqueue(existent.GetID()); 
        
    }
}

void Universe::CeaseExistent(Existent existent) { ceaseExistentQueue.Enqueue(existent); }

void Existent::Cease() { thisUniverse->CeaseExistent(*this); }



