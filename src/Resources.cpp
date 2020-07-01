#include "Resources.h"
#include "Spritesheet.h"
#include "Texture.h"
#include "Tile.h"
#include <fmt/core.h>

void Resources::Create() {
  m_Spritesheet.Create("./assets/spritesheets/main");

  const Sprite& player_sprite = m_Spritesheet.GetSprite("player.png");
  const Sprite& grass_sprite = m_Spritesheet.GetSprite("grass.png");
  const Sprite& dirt_sprite = m_Spritesheet.GetSprite("wall.png");

  m_Sprites.insert({Sprites::Player, player_sprite});
  m_Sprites.insert({Sprites::Grass, grass_sprite});
  m_Sprites.insert({Sprites::DirtWall, dirt_sprite});

  m_Tiles.insert({Tiles::Grass, Tile(grass_sprite)});
  m_Tiles.insert({Tiles::DirtWall, Tile(dirt_sprite)});
}

const Sprite& Resources::GetSprite(Resources::Sprites sprite_enum) const {
  auto it = m_Sprites.find(sprite_enum);
  if (it == m_Sprites.end()) {
    PANIC("Cannot find the sprite %d", (int) sprite_enum);
  }
  return it->second;
}

const Tile& Resources::GetTile(Resources::Tiles tile_enum) const {
  auto it = m_Tiles.find(tile_enum);
  if (it == m_Tiles.end()) {
    PANIC("Cannot find the tile %d", (int) tile_enum);
  }
  return it->second;
}
