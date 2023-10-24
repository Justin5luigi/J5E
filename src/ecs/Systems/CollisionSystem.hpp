#pragma once

#include "../ecs.hpp"
#include "../elements.hpp"
#include "../../logger.hpp"
#include "../../events/eventhandler.hpp"
#include "../../events/CollisionEvent.hpp"

struct Rect 
{
    double x;
    double y;
    double w;
    double h;
};

class CollisionSystem : public System
{
    public:
        CollisionSystem()
        {
            RequireElement<TransformElement>();
            RequireElement<ColliderElement>();
        }

        void Update(std::unique_ptr<EventHandler>& eventHandler)
        {
            auto existents = GetSystemExistents();
            for (auto i = existents.begin(); i != existents.end(); i++)
            {
                Existent a = *i;
                const auto atransform = a.GetElement<TransformElement>();
                const auto acollider = a.GetElement<ColliderElement>();
                Rect aRect = 
                {
                        atransform.position.x + acollider.offset.x,
                        atransform.position.y + acollider.offset.y,
                        acollider.size.x, 
                        acollider.size.y
                };
                
                for (auto j = i; j != existents.end(); j++)
                {
                    Existent b = *j;
                    if (a.Equals(b)) { continue; }
                    const auto btransform = b.GetElement<TransformElement>();
                    const auto bcollider = b.GetElement<ColliderElement>();
                    Rect bRect = 
                    {
                        btransform.position.x + bcollider.offset.x,
                        btransform.position.y + bcollider.offset.y,
                        bcollider.size.x, 
                        bcollider.size.y
                    };

                    if (AABBDoesCollide(aRect, bRect)) 
                    { 
                        eventHandler->EmitEvent<CollisionEvent>(a, b);
                        Logger::Log(LOG_INFO, "Collision happened poggers!");
                    }
                    
                }
            }
        }

    private:
        bool AABBDoesCollide(Rect a, Rect b)
        {
            return a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y;
        }
            
  
};
