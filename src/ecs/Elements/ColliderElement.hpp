#pragma once

#include <glm/glm.hpp>

struct ColliderElement
{
    glm::vec2 size;
    glm::vec2 offset;

    ColliderElement(glm::vec2 wh = glm::vec2(1, 1), glm::vec2 off = glm::vec2(0, 0))
    {
        this->size = wh;
        this->offset = off;
    }
};
