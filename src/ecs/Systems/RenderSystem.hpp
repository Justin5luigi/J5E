#pragma once

#include "../ecs.hpp"
#include "../elements.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../assetdatabase.hpp"

class RenderSystem : public System
{
    public:
        std::string name = "Render System";
        RenderSystem()
    {
        RequireElement<TransformElement>();
        RequireElement<SpriteElement>();
    }

    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetDataBase>& db)
    {
        //SORT BY SPRITE ZINDEX
        
        for (auto existent : GetSystemExistents())
        {
            const auto transform = existent.GetElement<TransformElement>();
            const auto sprite = existent.GetElement<SpriteElement>();
 
            auto thisTexture = db->GetTexture(sprite.textureID);
            
            SDL_Rect thisRect = 
                {
                    static_cast<int>(transform.position.x), 
                    static_cast<int>(transform.position.y), 
                    static_cast<int>(sprite.width * transform.scale.x), 
                    static_cast<int>(sprite.height * transform.scale.y)
                };
            SDL_Rect fakeRect = { 0, 0, thisRect.w, thisRect.h};
            SDL_RenderCopy(renderer, thisTexture, &fakeRect, &thisRect);
            //SDL_RenderCopyEx(renderer, thisTexture, &fakeRect, &thisRect, transform.rotation, NULL, SDL_FLIP_NONE);
        }
    }
};
