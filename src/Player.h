#pragma once


#include "Renderer.h"
#include "Events.h"
#include "m.h"
#include "debug.h"
#include "SpriteBatch.h"

class Player {
private:
    Sprite& m_Sprite;
    Events* m_Events;
    glm::vec2 m_Position;
    float m_Speed = 7.0f;

public:
    Player(Sprite& sprite, Events* events);
    void Update(double delta_time);
    void Draw(const SpriteBatch& sprite_batch);
};


