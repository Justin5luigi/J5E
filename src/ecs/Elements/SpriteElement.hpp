#pragma once
#include <string>
#include <cstdint>

struct SpriteElement 
{
    std::string textureID;
    float width;
    float height;
    uint32_t zidx;

    SpriteElement(std::string ID = "", float w = 0, float h = 0, uint32_t zindex = 0)
    {
        this->textureID = ID;
        this->width = w;
        this->height = h;
        this->zidx = zindex;
    }
};
