#include "game.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "logger.hpp"
#include "ecs/elements.hpp"
#include "ecs/systems.hpp"

Game::Game() 
{
    Logger::SetLogPath("./log");
    Logger::Log(LOG_INFO, "Game constructor initialized.");
    universe = std::make_unique<Universe>();
    assetDB = std::make_unique<AssetDataBase>();
    eventHandler = std::make_unique<EventHandler>();
    debugMode = false;
}

Game::~Game()
{
    Logger::Log(LOG_INFO, "destructor destructed"); 
}

void Game::Initialize()
{
    int ret = SDL_Init(SDL_INIT_EVERYTHING);
    
    if (ret != 0)
    {
        Logger::Log(LOG_ERROR, "Error initializing SDL.");
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("J5E", 0, 0, 800, 800, SDL_WINDOW_BORDERLESS);

    if (!window)
    {
        Logger::Log(LOG_ERROR, "Error creating SDL Window.");
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        Logger::Log(LOG_ERROR, "Error creating SDL renderer."); 
        exit(EXIT_FAILURE);
    }

    isRunning = true;
    prevTime = 0;
    Logger::Log(LOG_INFO, "Game initialized.");
}

void Game::Setup()
{
    //Adding Systems
    universe->AddSystem<MovementSystem>();
    universe->AddSystem<RenderSystem>();
    universe->AddSystem<CollisionSystem>();
    universe->AddSystem<RenderCollisionSystem>();
    universe->AddSystem<KeyBoardControlSystem>();
    
    //Adding assets
    assetDB->AddTexture(renderer, "test", "./assets/tank-panther-right.png");

    //Adding existents
    Existent god = universe->CreateExistent();
    Existent mortal = universe->CreateExistent();

    //Adding elements
    god.AddElement<TransformElement>(glm::vec2(10, 10), glm::vec2(1, 1), 0);
    god.AddElement<RigidBodyElement>(glm::vec2(10, 0));
    god.AddElement<SpriteElement>("test", 32, 32);
    god.AddElement<ColliderElement>(glm::vec2(32, 32));
    mortal.AddElement<TransformElement>(glm::vec2(100, 10), glm::vec2(1, 1), 0);
    mortal.AddElement<RigidBodyElement>(glm::vec2(-1,0));
    mortal.AddElement<SpriteElement>("test", 32, 32);
    mortal.AddElement<ColliderElement>(glm::vec2(32, 32));

    //subscribing to events
    universe->GetSystem<KeyBoardControlSystem>().ListenToEvents(eventHandler);
}

void Game::Run()
{
    while (isRunning)
    {
        currTime = SDL_GetTicks();
        delta = (float)(currTime - prevTime) / 1000.0;
        prevTime = currTime;
        //Logger::Log(LOG_INFO, "FPS: " + std::to_string(1.0 / delta));
        Input();
        Update(delta);
        Render();
    }
}

void Game::Input()
{
    //std::cout << "Inputing..." << std::endl;
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                eventHandler->EmitEvent<KeyPressedEvent>(e.key.keysym.sym);
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;

                    case SDLK_d:
                        debugMode = !debugMode;
                        break;
                } 
        }
    }
    
}

void Game::Update(double delta)
{
    //std::cout << "updating..." << std::endl;
    universe->Update();
    universe->GetSystem<MovementSystem>().Update(delta);
    universe->GetSystem<CollisionSystem>().Update(eventHandler);
    
}

void Game::Render()
{
    //Rendering Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    universe->GetSystem<RenderSystem>().Update(renderer, assetDB);
    if (debugMode) { universe->GetSystem<RenderCollisionSystem>().Update(renderer); }
    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    Logger::Log(LOG_INFO, "destroying...");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    Logger::Close();
}
