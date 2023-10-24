#pragma once

#include <SDL2/SDL.h>
#include "ecs/ecs.hpp"
#include <memory>
#include "assetdatabase.hpp"
#include <cstdint>
#include "events/eventhandler.hpp"

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

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool isRunning;
        void RenderImage(const char *imgPath);
        std::unique_ptr<Universe> universe;
        std::unique_ptr<AssetDataBase> assetDB;
        std::unique_ptr<EventHandler> eventHandler;
        
                
};