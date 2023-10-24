#pragma once
#include <glm/glm.hpp>
#include <string>

struct TransformElement 
{
    glm::vec2 position;
    glm::vec2 scale;
    double rotation;

    TransformElement(glm::vec2 pos = glm::vec2(0, 0), glm::vec2 scale = glm::vec2(1, 1), double rotation = 0)
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
