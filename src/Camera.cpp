//
// Created by Arnaud Valensi on 12/02/2020.
//

#include "Camera.h"
#include "Events.h"
#include "Renderer.h"
#include "debug.h"
#include "m.h"
#include <fmt/core.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(Events& event, Renderer& renderer)
    : m_Events(event), m_Renderer(renderer) {
  m_Position = glm::vec3(0.0f, 0.0f, 30.0f);
  m_VerticalSizeInUnit = m_ZoomMin;
  m_TargetVerticalSize = m_VerticalSizeInUnit;

  UpdateProjectionMatrix();

  renderer.OnScreenSizeChange([&]() {
    UpdateProjectionMatrix();
  });
}

void Camera::UpdateProjectionMatrix() {
  auto screen_size = m_Renderer.GetScreenSize();
  float horizontal_size_in_unit = m_VerticalSizeInUnit * ((double) screen_size.x / screen_size.y);
  float half_height = m_VerticalSizeInUnit / 2.0f;
  float half_width = horizontal_size_in_unit / 2.0f;

  m_ProjectionMatrix = glm::ortho<float>(
    -half_width,
    half_width,
    -half_height,
    half_height,
    // TODO: Set to a positive value.
    -1.0f,
    100.0f);
}

void Camera::Update(double delta_time) {
  glm::vec2 input = m::vec2_zero;

  if (m_Events.GetKeyDown(SDLK_d)) {
    input += m::vec2_right;
  }
  if (m_Events.GetKeyDown(SDLK_a)) {
    input += m::vec2_left;
  }
  if (m_Events.GetKeyDown(SDLK_w)) {
    input += m::vec2_up;
  }
  if (m_Events.GetKeyDown(SDLK_s)) {
    input += m::vec2_down;
  }

  glm::vec2 direction = m::safe_normalize(input);
  glm::vec2 velocity = direction * 10.0f;
  glm::vec3 new_position =
    m_Position + glm::vec3(velocity.x, velocity.y, 0.0f) * (float) delta_time;
  m_Position = new_position;

  // Zoom.
  int vertical_scroll = m_Events.GetVerticalMouseScroll();
  if (vertical_scroll != 0) {
    m_TargetVerticalSize -= vertical_scroll * m_ZoomStepScale;
    m_TargetVerticalSize = glm::clamp(m_TargetVerticalSize, m_ZoomMin, m_ZoomMax);
  }

  if (m_TargetVerticalSize != m_VerticalSizeInUnit) {
    m_VerticalSizeInUnit = m::smooth_damp(
      m_VerticalSizeInUnit,
      m_TargetVerticalSize,
      m_CurrentZoomVelocity,
      0.1,
      INFINITY,
      delta_time);

    if (glm::abs(m_VerticalSizeInUnit - m_TargetVerticalSize) < 0.0001f) {
      m_VerticalSizeInUnit = m_TargetVerticalSize;
    }

    UpdateProjectionMatrix();
  }
}

glm::mat4 Camera::GetViewMatrix() const {
  auto view_matrix = glm::mat4(1.0f);

  // Note that we're translating the scene in the reverse direction of where we want to move
  view_matrix = glm::translate(view_matrix, -m_Position);

  return view_matrix;
}

glm::mat4 Camera::GetProjectionMatrix() const {
  return m_ProjectionMatrix;
}
