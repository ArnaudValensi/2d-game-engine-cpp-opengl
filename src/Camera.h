//
// Created by Arnaud Valensi on 12/02/2020.
//

#pragma once


#include <glm/glm.hpp>
#include "Events.h"
#include "Renderer.h"

class Camera {
private:
    Events& m_Events;
    Renderer& m_Renderer;
    glm::vec3 m_Position;
    glm::mat4 m_ProjectionMatrix;
    float m_VerticalSizeInUnit;
    float m_TargetVerticalSize;
    float m_CurrentZoomVelocity;
    float m_ZoomMin = 10.0f;
    float m_ZoomMax = 100.0;
    float m_ZoomStepScale = 1.0f;

public:
    Camera(Events& event, Renderer& renderer);
    void Update(double delta_time);
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    void UpdateProjectionMatrix();
};


