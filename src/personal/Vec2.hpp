#pragma once

class Vec2
{
    public:
        Vec2(float x = 0, float y = 0) 
        {
            this->x = x;
            this->y = y;
        }
        ~Vec2() = default;
        
        float x;
        float y;

        Vec2 Add(Vec2 a, Vec2 b) { return Vec2(a.x + b.x, a.y + b.y); }
        Vec2 Subtract(Vec2 a, Vec2 b) { return Vec2(a.x - b.x, a.y - b.y); }
        Vec2 Scale(float c, Vec2 a) { return Vec2(a.x * c, a.y * c); }
};
