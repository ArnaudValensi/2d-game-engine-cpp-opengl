#include <glm/glm.hpp>
#include "Rect.h"

Rect::Rect(float x, float y, float width, float height) {
    m_X = x;
    m_Y = y;
    m_Width = width;
    m_Height = height;
}

float Rect::X() const {
    return m_X;
}

float Rect::Y() const {
    return m_Y;
}

float Rect::Width() const {
    return m_Width;
}

float Rect::Height() const {
    return m_Height;
}

bool Rect::Overlap(const Rect other) const {
    return other.XMax() > XMin()
           && other.XMin() < XMax()
           && other.YMax() > YMin()
           && other.YMin() < YMax();
}

float Rect::XMin() const {
    return m_X;
}

float Rect::XMax() const {
    return m_X + m_Width;
}

float Rect::YMin() const {
    return m_Y;
}

float Rect::YMax() const {
    return m_Y + m_Height;
}

float Rect::X(float x) {
    m_X = x;
    return m_X;
}

float Rect::Y(float y) {
    m_Y = y;
    return m_Y;
}

glm::vec2 Rect::Position() const {
    return {m_X, m_Y};
}

glm::vec2 Rect::Size() const {
    return {m_Width, m_Height};
}

