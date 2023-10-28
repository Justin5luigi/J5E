#include "luabindings.hpp"
#include "logger.hpp"
#include "SDL2/SDL.h"
#include "ecs/systems.hpp"

void LuaBindings::LuaSetPosition(Existent existent, double x, double y)
{
    existent.GetElement<TransformElement>().position.x = x;
    existent.GetElement<TransformElement>().position.y = y;
}

bool LuaBindings::LuaKeyPressed(Existent existent, std::string keysym)
{
    SDL_Keycode key = existent.thisUniverse->GetSystem<KeyBoardControlSystem>().GetKey(keysym);
    return existent.thisUniverse->GetSystem<KeyBoardControlSystem>().isKeyPressed(key);
}

void LuaBindings::LuaSetVelocity(Existent existent, double x, double y)
{
    existent.GetElement<RigidBodyElement>().velocity.x = x;
    existent.GetElement<RigidBodyElement>().velocity.y = y;
}

void LuaBindings::LuaLog(std::string msg) { Logger::Log(LOG_DEBUG, msg); }

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
     lua.set_function("IsKeyPressed", &LuaBindings::LuaKeyPressed, this);
     lua.set_function("SetVelocity", &LuaBindings::LuaSetVelocity, this);
     lua.set_function("Log", &LuaBindings::LuaLog, this);
}

LuaBindings::LuaBindings() 
{ 
    Logger::Log(LOG_INFO, "LuaBindings constructor initialized.");
}

LuaBindings::~LuaBindings() { Logger::Log(LOG_INFO, "LuaBindings destructor called."); }
