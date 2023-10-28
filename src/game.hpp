#pragma once

#include <SDL2/SDL.h>
#include "ecs/ecs.hpp"
#include <memory>
#include "assetdatabase.hpp"
#include <cstdint>
#include "events/eventhandler.hpp"
#include "logger.hpp"
#include "ecs/elements.hpp"
#include "ecs/systems.hpp"
#include <sol/sol.hpp>
#include "luabindings.hpp"


class Game 
{
    public:
        Game();
        ~Game();
        void Initialize();
        void Setup();
        void Run();
        void Input();
        void Update(double delta);
        void Render();
        void Destroy();
        double delta;
        uint32_t prevTime, currTime;
        bool debugMode;
        

        //getters
        SDL_Window* GetGameWindow() const;
        SDL_Renderer* GetGameRenderer() const;
        std::unique_ptr<Universe>& GetGameUniverse();
        std::unique_ptr<AssetDataBase>& GetGameAssetDB();
        std::unique_ptr<EventHandler>& GetGameEventHandler();
        sol::state lua;
        LuaBindings luaBindings;

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool isRunning;
        void RenderImage(const char *imgPath);
        std::unique_ptr<Universe> universe;
        std::unique_ptr<AssetDataBase> assetDB;
        std::unique_ptr<EventHandler> eventHandler;
        void LoadAssets(std::string luaFile);  
        void SetLuaBindings();      
                
};
