#pragma once

#include <sol/sol.hpp>
#include "ecs/ecs.hpp"
#include "ecs/elements.hpp"

class LuaBindings
{
    public:
        LuaBindings();
        ~LuaBindings();
        void SetBindings(sol::state& lua);
        void LuaSetPosition(Existent existent, double x, double y);
        void TestFunction();
};
