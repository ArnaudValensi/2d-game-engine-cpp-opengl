#include "Tilemap.h"
#include "SpriteBatch.h"

Tilemap::Tilemap()
    : tiles() {
}

void Tilemap::SetTile(int x, int y, const Tile& tile) {
  assert(x < SIZE && y < SIZE);
  tiles[y][x] = &tile;
}

void Tilemap::Draw(const SpriteBatch& sprite_batch) const {
  for (int y = 0; y < SIZE; ++y) {
    for (int x = 0; x < SIZE; ++x) {
      const Tile* tile = tiles[y][x];

      if (tile != nullptr) {
        sprite_batch.Draw(tile->GetSprite(), {x, y, 0.0f});
      }
    }
  }
}
