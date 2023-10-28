#pragma once

#include "../ecs.hpp"
#include "../elements.hpp"
#include <sol/sol.hpp>
#include <map>
#include "../../events/events.hpp"


class ScriptSystem : public System
{
    public:
        ScriptSystem()
        {
            RequireElement<ScriptElement>();
        }

        //std::map<uint32_t, sol::function> updateFunctions;
        //sol::state lua;
        void ListenToEvents(std::unique_ptr<EventHandler>& eventHandler) 
        { eventHandler->ListenToEvent(this, &ScriptSystem::OnScriptCollision); }

        void Update(double delta, sol::state& lua)
        {
            for (auto existent : GetSystemExistents())
            {
                //sol::function f = updateFunctions[existent.GetID()];
               //f();
               lua.set("this", existent);
               auto f = existent.GetElement<ScriptElement>().updateFunc;
               f(delta);
            }
        }

        void OnScriptCollision(CollisionEvent& event)
        {
            //Logger::Log(LOG_INFO, "I do make it in here at least");
            
            if (event.a.ElementExists<ScriptElement>())
            {
                auto Collide = event.a.GetElement<ScriptElement>().OnCollisionFunc;
                if (Collide != sol::nil) { Collide(event.b); }
            }

            if (event.b.ElementExists<ScriptElement>())
            {
                auto Collide = event.b.GetElement<ScriptElement>().OnCollisionFunc;
                if (Collide != sol::nil) { Collide(event.a); }
            }

            
        }
  
};
