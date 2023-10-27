#pragma once

#include "../ecs.hpp"
#include "../elements.hpp"
#include <sol/sol.hpp>
#include <map>


class ScriptSystem : public System
{
    public:
        ScriptSystem()
        {
            RequireElement<ScriptElement>();
        }

        //std::map<uint32_t, sol::function> updateFunctions;
        //sol::state lua;

        void Update(double delta, sol::state& lua)
        {
            for (auto existent : GetSystemExistents())
            {
                //sol::function f = updateFunctions[existent.GetID()];
               //f();
               lua.set("this", existent);
               lua.set("test", "Somehow this is getting through?");
               auto f = existent.GetElement<ScriptElement>().thisFunc;
               f(delta);
            }
        }
  
};
