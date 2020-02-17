#include "Tile.h"
#include "Sprite.h"

Tile::Tile(const Sprite& sprite) : m_Sprite(sprite) {

}

const Sprite& Tile::GetSprite() const {
    return m_Sprite;
}

