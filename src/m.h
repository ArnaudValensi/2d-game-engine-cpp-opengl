#pragma once

#include <glm/glm.hpp>

namespace m {
  template<typename T>
  int floor_to_int(T value) {
    return glm::floor(value);
  }

  template<typename T>
  T safe_normalize(T value) {
    return value == glm::vec2(0, 0) ? value : glm::normalize(value);
  }

  const glm::vec2 vec2_zero = glm::vec2(0.0, 0.0);
  const glm::vec2 vec2_up = glm::vec2(0.0, 1.0);
  const glm::vec2 vec2_down = glm::vec2(0.0, -1.0);
  const glm::vec2 vec2_left = glm::vec2(-1.0, 0.0);
  const glm::vec2 vec2_right = glm::vec2(1.0, 0.0);

  float smooth_damp(
    float current,
    float target,
    float& currentVelocity,
    float smoothTime,
    float maxSpeed,
    float deltaTime);

  glm::vec2 smooth_damp(
    glm::vec2 current,
    glm::vec2 target,
    glm::vec2& currentVelocity,
    float smoothTime,
    float maxSpeed,
    float deltaTime);
} // namespace m
