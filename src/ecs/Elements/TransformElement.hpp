#pragma once
#include "../../personal/Vec2.hpp"
#include <string>

struct TransformElement 
{
    Vec2 position;
    Vec2 scale;
    double rotation;

    TransformElement(Vec2 pos = Vec2(0, 0), Vec2 scale = Vec2(1, 1), double rotation = 0)
    {
        this->position = pos;
        this->scale = scale;
        this->rotation = rotation;
    }

    std::string ToString()
    {
        return "Pos: x=" + std::to_string(position.x) + " y=" + std::to_string(position.y)
        + " Scale: x=" + std::to_string(scale.x) + " y=" + std::to_string(scale.y)
        + " rotation: " + std::to_string(rotation);
    }    
};
