#pragma once

#include <map>
#include <typeindex>
#include <list>
#include <functional>
#include "event.hpp"
//#include "events.hpp"
#include <memory>

class ICall
{
    private:
        virtual void Call(Event& e) = 0;
        
    public:
        virtual ~ICall() = default;
        void Execute(Event& e) { Call(e); }

    
};

template <typename TOwner, typename T>
class EventCallBack : public ICall
{
    
    private:
        typedef void (TOwner::*CallBackFunction)(T&);
        TOwner* ownerInstance;
        CallBackFunction callBackFunction;
        virtual void Call(Event& e) override { std::invoke(callBackFunction, ownerInstance, static_cast<T&>(e)); }

    public:
        EventCallBack(TOwner* ownerInstance, CallBackFunction callBackFunction)
        {
            this->ownerInstance = ownerInstance;
            this->callBackFunction = callBackFunction;
        }

        virtual ~EventCallBack() override = default;
};

typedef std::list<std::unique_ptr<ICall>> callBackList;

class EventHandler
{
    private:
        std::map<std::type_index, std::unique_ptr<callBackList>> listeners;
        
    public:
        EventHandler() = default;
        ~EventHandler() = default;
        template <typename TOwner, typename T>
        void ListenToEvent(TOwner* ownerInstance, void (TOwner::*callBackFunction)(T&))
        {
            if (!listeners[typeid(T)].get())
            {
                listeners[typeid(T)] = std::make_unique<callBackList>();
            }
            auto listener = std::make_unique<EventCallBack<TOwner,T>>(ownerInstance, callBackFunction);
            listeners[typeid(T)]->push_back(std::move(listener));
        }

        template <typename T, typename ...TArgs>
        void EmitEvent(TArgs&& ...args)
        {
            auto handlers = listeners[typeid(T)].get();
            if (handlers)
            {
                for (auto i = handlers->begin(); i != handlers->end(); i++)
                {
                    auto handler = i->get();
                    T event(std::forward<TArgs>(args)...);
                    handler->Execute(event);
                }
            }
        }

    
  
};
