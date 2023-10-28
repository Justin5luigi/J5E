#pragma once

#include "../../personal/Vec2.hpp"

struct ColliderElement
{
    Vec2 size;
    Vec2 offset;

    ColliderElement(Vec2 wh = Vec2(1, 1), Vec2 off = Vec2(0, 0))
    {
        this->size = wh;
        this->offset = off;
    }
};
