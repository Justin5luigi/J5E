#pragma once

#include <string>
#include <sol/sol.hpp>

struct ScriptElement
{
    std::string scriptPath;
    sol::function updateFunc;
    sol::function OnCollisionFunc;

    ScriptElement(std::string thisScriptPath = "", sol::function f = sol::nil, sol::function c = sol::nil)
    {
        this->scriptPath = thisScriptPath;
        this->updateFunc = f;
        this->OnCollisionFunc = c;
    }
};
