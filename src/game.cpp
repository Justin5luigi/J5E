#include "game.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "personal/Vec2.hpp"

Game::Game() 
{
    Logger::SetLogPath("./logfile.txt");
    //Logger::SetLoggingType(LOG_FILE_ONLY);
    Logger::Log(LOG_INFO, "Game constructor initialized.");
    universe = std::make_unique<Universe>();
    assetDB = std::make_unique<AssetDataBase>();
    eventHandler = std::make_unique<EventHandler>();
    debugMode = false;
    luaBindings = LuaBindings();
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
    universe->AddSystem<ScriptSystem>();
    
    LoadAssets("./game.lua");
    luaBindings.SetBindings(lua);
    //subscribing to events
    universe->GetSystem<KeyBoardControlSystem>().ListenToEvents(eventHandler);
    universe->GetSystem<ScriptSystem>().ListenToEvents(eventHandler);
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
        universe->GetSystem<KeyBoardControlSystem>().ClearKeyBoardMask();
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
    universe->GetSystem<CollisionSystem>().Update(eventHandler, lua);
    universe->GetSystem<ScriptSystem>().Update(delta, lua);
    
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

//setter functions 
SDL_Window* Game::GetGameWindow() const { return window; }

SDL_Renderer* Game::GetGameRenderer() const { return renderer; }

std::unique_ptr<Universe>& Game::GetGameUniverse() { return universe; }
        
std::unique_ptr<AssetDataBase>& Game::GetGameAssetDB() { return assetDB; }
        
std::unique_ptr<EventHandler>& Game::GetGameEventHandler() { return eventHandler; }


void Game::LoadAssets(std::string luaFile)
{
    lua.open_libraries(sol::lib::base, sol::lib::math);
    sol::load_result script = lua.load_file(luaFile);
    if (!script.valid())
    {
        Logger::Log(LOG_ERROR, sol::error(script).what());
        return;
    }

    lua.script_file(luaFile);
    sol::table assets = lua["Assets"];
    bool stillArgsToParse = true;
    int i = 0;
    while (stillArgsToParse)
    {
        sol::optional<sol::table> isasset = assets[i];
        if (isasset == sol::nullopt) { stillArgsToParse = false; }
        else
        {
            sol::table asset = assets[i];
            std::string assetType = asset["type"];
            std::string assetID = asset["id"];
            std::string filePath = asset["file"];
            assetDB->AddTexture(renderer, assetID, filePath);
            Logger::Log(LOG_INFO, "Successfully loaded texture from lua with id = " + assetID);
            i++;
        }
    }

    sol::table Existents = lua["Existents"];
    stillArgsToParse = true;
    i = 0;

    while (stillArgsToParse)
    {
        sol::optional<sol::table> isExistent = Existents[i];
        if (isExistent == sol::nullopt) { stillArgsToParse = false; }
        else
        {
            sol::table existent = Existents[i];
            Existent newExistent = universe->CreateExistent();
            bool stillElementstoParse = true;
            int j = 1;
            sol::table Elements = existent["elements"];
            while (stillElementstoParse)
            {
                sol::optional<sol::table> isElement = Elements[j];
                if (isElement == sol::nullopt) { stillElementstoParse = false; }
                else
                {
                    sol::table element = Elements[j];
                    std::string type = element["type"];
                    
                    if (type == "TransformElement")
                    {
                        double xpos = element["xpos"];
                        double ypos = element["ypos"];
                        double xscale = element["xscale"];
                        double yscale = element["yscale"];
                        double rotation = element["rotation"];
                        newExistent.AddElement<TransformElement>(Vec2(xpos, ypos), Vec2(xscale, yscale), rotation);
                    }

                    else if (type == "RigidBodyElement")
                    {
                        double xspd = element["xspd"];
                        double yspd = element["yspd"];
                        newExistent.AddElement<RigidBodyElement>(Vec2(xspd, yspd));
                    }

                    else if (type == "SpriteElement")
                    {
                        std::string id = element["assetID"];
                        double width = element["w"];
                        double height = element["h"];
                        newExistent.AddElement<SpriteElement>(id, width, height);
                    }

                    else if (type == "ColliderElement")
                    {
                        double width = element["w"];
                        double height = element["h"];
                        newExistent.AddElement<ColliderElement>(Vec2(width, height));
                    }

                    else if (type == "ScriptElement")
                    {
                        std::string scriptPath = element["scriptPath"];
                        //attempting to find scripts update function
                        sol::load_result result = lua.load_file(scriptPath);
                        if (!result.valid())
                        {
                            Logger::Log(LOG_ERROR, sol::error(result).what());
                            continue;
                        }
                        
                        lua.script_file(scriptPath);
                        sol::function updateFunction = lua["Update"];
                        if (updateFunction.valid()) 
                        { 
                            newExistent.AddElement<ScriptElement>(scriptPath, updateFunction);
                            Logger::Log(LOG_INFO, "Found Update function inside script file " + scriptPath);
                        }
                        else { Logger::Log(LOG_ERROR, "Could not find Update function inside script file " + scriptPath); }
                        sol::function CollisionFunction = lua["OnCollision"];
                        if (CollisionFunction.valid()) 
                        {
                            Logger::Log(1, "OnCollision function found in script " + scriptPath);
                            newExistent.GetElement<ScriptElement>().OnCollisionFunc = CollisionFunction;
                        }
                        else { Logger::Log(1, "Could not find OnCollision function in script " + scriptPath); }
                    }
                    j++;
                }
            }
            i++;
        }
    }
}
