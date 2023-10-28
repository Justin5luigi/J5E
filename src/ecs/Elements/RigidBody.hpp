#pragma once

#include "../../personal/Vec2.hpp"
#include <string>

struct RigidBodyElement
{
  Vec2 velocity;

  RigidBodyElement(Vec2 vel = Vec2(1, 1)) { this->velocity = vel; }
  std::string ToString() const
  {
      return "Velocity: x=" + std::to_string(velocity.x) + " y=" + std::to_string(velocity.y);
  }
};
