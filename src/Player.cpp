#include <SDL_keycode.h>
#include "Player.h"
#include "Renderer.h"
#include "m.h"

Player::Player(Sprite& sprite, Events* events) :
        m_Sprite(sprite),
        m_Events(events),
        m_Position(m::vec2_zero) {}

void Player::Update(double delta_time) {
    glm::vec2 input = m::vec2_zero;

    if (m_Events->GetKeyDown(SDLK_RIGHT)) {
        input += m::vec2_right;
    }
    if (m_Events->GetKeyDown(SDLK_LEFT)) {
        input += m::vec2_left;
    }
    if (m_Events->GetKeyDown(SDLK_UP)) {
        input += m::vec2_up;
    }
    if (m_Events->GetKeyDown(SDLK_DOWN)) {
        input += m::vec2_down;
    }

    glm::vec2 direction = m::safe_normalize(input);
    glm::vec2 velocity = direction * m_Speed;
    glm::vec2 new_position = m_Position + velocity * (float) delta_time;
    m_Position = new_position;
}

void Player::Draw(const SpriteBatch& sprite_batch) {
    sprite_batch.Draw(m_Sprite, glm::vec3(m_Position, 1.0f));
}
