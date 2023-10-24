#pragma once

#include "glm/glm.hpp"
#include <string>

struct RigidBodyElement
{
  glm::vec2 velocity;

  RigidBodyElement(glm::vec2 vel = glm::vec2(1, 1)) { this->velocity = vel; }
  std::string ToString() const
  {
      return "Velocity: x=" + std::to_string(velocity.x) + " y=" + std::to_string(velocity.y);
  }
};
