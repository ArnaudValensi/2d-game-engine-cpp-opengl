//
// Created by Arnaud Valensi on 13/02/2020.
//

#include "Sprite.h"

Sprite::Sprite(Texture* texture, int x, int y, int width, int height)
    : m_Texture(texture), m_Rect(x, y, width, height) {
}

const Texture& Sprite::GetTexture() const {
  return *m_Texture;
}

Rect Sprite::GetRect() const {
  return m_Rect;
}
