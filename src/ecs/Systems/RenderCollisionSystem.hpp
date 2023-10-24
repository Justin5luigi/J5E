#pragma once

#include "../ecs.hpp"
#include "../elements.hpp"
#include "SDL2/SDL.h"

class RenderCollisionSystem : public System
{
    public:
        RenderCollisionSystem()
        {
            RequireElement<TransformElement>();
            RequireElement<ColliderElement>();
        }

        void Update(SDL_Renderer* renderer)
        {
            for (auto existent : GetSystemExistents())
            {
                    const auto transform = existent.GetElement<TransformElement>();
                    const auto collider = existent.GetElement<ColliderElement>();

                    SDL_Rect thisRect = 
                    {
                            static_cast<int>(transform.position.x + collider.offset.x),
                            static_cast<int>(transform.position.y + collider.offset.y),
                            static_cast<int>(collider.size.x),
                            static_cast<int>(collider.size.y)
                    };
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderDrawRect(renderer, &thisRect);
            }
        }
};
