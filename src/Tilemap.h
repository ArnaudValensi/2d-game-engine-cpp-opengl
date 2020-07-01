#pragma once

#include "Renderer.h"
#include "SpriteBatch.h"
#include "Tile.h"

class Tilemap {
private:
  static const int SIZE = 32;
  const Tile* tiles[SIZE][SIZE];

public:
  Tilemap();
  void Draw(const SpriteBatch& sprite_batch) const;
  void SetTile(int x, int y, const Tile& tile);
};
