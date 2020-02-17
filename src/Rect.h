#pragma once


#include <glm/fwd.hpp>

class Rect {
private:
    float m_X;
    float m_Y;
    float m_Width;
    float m_Height;

public:
    Rect(float x, float y, float width, float height);
    Rect() = default;
    [[nodiscard]] float X() const;
    [[nodiscard]] float Y() const;
    [[nodiscard]] float Width() const;
    [[nodiscard]] float Height() const;
    [[nodiscard]] float XMin() const;
    [[nodiscard]] float XMax() const;
    [[nodiscard]] float YMin() const;
    [[nodiscard]] float YMax() const;
    [[nodiscard]] glm::vec2 Position() const;
    [[nodiscard]] glm::vec2 Size() const;

    // Setting X or Y with move the rect rather that resize it.
    float X(float x);
    float Y(float y);

    bool Overlap(const Rect other) const;
};


