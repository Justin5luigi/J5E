#pragma once

#include <string>
#include <sol/sol.hpp>

struct ScriptElement
{
    std::string scriptPath;
    sol::function thisFunc;

    ScriptElement(std::string thisScriptPath = "", sol::function f = sol::nil)
    {
        this->scriptPath = thisScriptPath;
        this->thisFunc = f;
    }
};
