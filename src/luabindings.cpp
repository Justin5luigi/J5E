#include "luabindings.hpp"
#include "logger.hpp"

void LuaBindings::LuaSetPosition(Existent existent, double x, double y)
{
    existent.GetElement<TransformElement>().position.x = x;
    existent.GetElement<TransformElement>().position.y = y;
}



void LuaBindings::SetBindings(sol::state& lua)
{
    Logger::Log(LOG_INFO, "Creating lua bindings...");
    //creating usertype bindings
    lua.new_usertype<Existent>("existent", 
               "GetID", &Existent::GetID, 
               "Cease", &Existent::Cease,
               "GetTag", &Existent::GetTag,
               "Equals", &Existent::Equals
               );

     //creating function bindings
     lua.set_function("SetPosition", &LuaBindings::LuaSetPosition, this);
}

LuaBindings::LuaBindings() { Logger::Log(LOG_INFO, "LuaBindings constructor initialized."); }

LuaBindings::~LuaBindings() { Logger::Log(LOG_INFO, "LuaBindings destructor called."); }
