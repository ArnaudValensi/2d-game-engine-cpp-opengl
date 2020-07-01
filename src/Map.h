#pragma once

#include "Renderer.h"
#include "Resources.h"
#include "Tile.h"
#include "Tilemap.h"

class Map {
private:
  Tilemap m_GroundTilemap;

public:
  void Draw(const SpriteBatch& sprite_batch) const;
  void Init(Resources& resources, const char* map_path);
};
