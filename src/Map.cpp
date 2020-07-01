#include "Map.h"
#include "Resources.h"
#include "debug.h"
#include <fstream>
#include <iostream>

void Map::Init(Resources& resources, const char* map_path) {
  const Tile& grass_tile = resources.GetTile(Resources::Tiles::Grass);
  const Tile& dirt_wall_tile = resources.GetTile(Resources::Tiles::DirtWall);

  std::ifstream fin(map_path);
  int width;
  int height;

  if (!(fin >> width)) {
    PANIC("Cannot parse map width");
  }

  if (!(fin >> height)) {
    PANIC("Cannot parse map height");
  }

  char map_line[128];
  for (int y = 0; y < height; ++y) {
    memset(map_line, 0, sizeof(map_line));
    if (!(fin >> map_line)) {
      PANIC("Cannot parse map row %d: line is probably missing.", y);
    }

    int line_size = strlen(map_line);
    if (line_size != width) {
      PANIC("Cannot parse map row %d: expected size %d, actual %d.", y, width, line_size);
    }

    for (int x = 0; x < width; ++x) {
      char tile_type = map_line[x];

      if (tile_type == '#') {
        m_GroundTilemap.SetTile(x, y, dirt_wall_tile);
      }
      else if (tile_type == '.') {
        m_GroundTilemap.SetTile(x, y, grass_tile);
      }
      else {
        PANIC("Unknown map tile at (%d, %d).", x, y);
      }
    }
  }
}

void Map::Draw(const SpriteBatch& sprite_batch) const {
  m_GroundTilemap.Draw(sprite_batch);
}
