#pragma once
#include "../ecs.hpp"
#include "../elements.hpp"

class MovementSystem : public System
{
    public:
        std::string name = "Movement System";
        MovementSystem()
    {
        RequireElement<TransformElement>();
        RequireElement<RigidBodyElement>();
    }

    void Update(double delta)
    {
        for (auto existent : GetSystemExistents())
        {
            auto& transform = existent.GetElement<TransformElement>();
            const auto rigidBody = existent.GetElement<RigidBodyElement>();
            //Logger::Log(LOG_INFO, transform.ToString());
            //Logger::Log(LOG_INFO, rigidBody.ToString());

            transform.position.x += rigidBody.velocity.x * delta;
            transform.position.y += rigidBody.velocity.y * delta; 
            //Logger::Log(LOG_INFO, transform.ToString());
            
        }
    }
};
