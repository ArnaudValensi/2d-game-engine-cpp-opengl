#include "m.h"
#include <glm/glm.hpp>

float m::smooth_damp(
  float current,
  float target,
  float& currentVelocity,
  float smoothTime,
  float maxSpeed,
  float deltaTime) {
  smoothTime = glm::max(0.0001f, smoothTime);
  float omega = 2.0f / smoothTime;
  float x = omega * deltaTime;
  float exp = (float) (1.0 / (1.0 + (double) x + 0.479999989271164 * (double) x * (double) x + 0.234999999403954 * (double) x * (double) x * (double) x));
  float delta_x = current - target;
  float target2 = target;
  float max_delta = maxSpeed * smoothTime;
  float num6 = glm::clamp(delta_x, -max_delta, max_delta);
  target = current - num6;
  float num7 = (currentVelocity + omega * num6) * deltaTime;
  currentVelocity = (currentVelocity - omega * num7) * exp;
  float result = target + (num6 + num7) * exp;
  if ((double) target2 - (double) current > 0.0 == (double) result > (double) target2) {
    result = target2;
    currentVelocity = (result - target2) / deltaTime;
  }
  return result;
}

// https://graemepottsfolio.wordpress.com/tag/damped-spring/
glm::vec2 m::smooth_damp(
  glm::vec2 current,
  glm::vec2 target,
  glm::vec2& currentVelocity,
  float smoothTime,
  float maxSpeed,
  float deltaTime) {
  smoothTime = glm::max(0.0001f, smoothTime);
  float omega = 2.0f / smoothTime;
  float num2 = omega * deltaTime;
  float exp = (float) (1.0 / (1.0 + (double) num2 + 0.479999989271164 * (double) num2 * (double) num2 + 0.234999999403954 * (double) num2 * (double) num2 * (double) num2));
  float num4 = current.x - target.x;
  float num5 = current.y - target.y;
  glm::vec2 vector2 = target;
  float num6 = maxSpeed * smoothTime;
  float num7 = num6 * num6;
  float num8 = (float) ((double) num4 * (double) num4 + (double) num5 * (double) num5);
  if ((double) num8 > (double) num7) {
    float num9 = (float) glm::sqrt((double) num8);
    num4 = num4 / num9 * num6;
    num5 = num5 / num9 * num6;
  }
  target.x = current.x - num4;
  target.y = current.y - num5;
  float num10 = (currentVelocity.x + omega * num4) * deltaTime;
  float num11 = (currentVelocity.y + omega * num5) * deltaTime;
  currentVelocity.x = (currentVelocity.x - omega * num10) * exp;
  currentVelocity.y = (currentVelocity.y - omega * num11) * exp;
  float x = target.x + (num4 + num10) * exp;
  float y = target.y + (num5 + num11) * exp;
  float num12 = vector2.x - current.x;
  float num13 = vector2.y - current.y;
  float num14 = x - vector2.x;
  float num15 = y - vector2.y;
  if ((double) num12 * (double) num14 + (double) num13 * (double) num15 > 0.0) {
    x = vector2.x;
    y = vector2.y;
    currentVelocity.x = (x - vector2.x) / deltaTime;
    currentVelocity.y = (y - vector2.y) / deltaTime;
  }

  return glm::vec2(x, y);
}
