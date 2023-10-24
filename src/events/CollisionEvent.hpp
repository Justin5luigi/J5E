#pragma once

#include "../ecs/ecs.hpp"
#include "event.hpp"


class CollisionEvent : public Event
{
    public:
        Existent a;
        Existent b;
        CollisionEvent(Existent a, Existent b) : a(a), b(b) {}
};
