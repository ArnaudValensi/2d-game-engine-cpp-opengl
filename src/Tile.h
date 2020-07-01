#pragma once

#include "Sprite.h"

class Tile {
private:
  const Sprite& m_Sprite;

public:
  explicit Tile(const Sprite& sprite);
  [[nodiscard]] const Sprite& GetSprite() const;
};
