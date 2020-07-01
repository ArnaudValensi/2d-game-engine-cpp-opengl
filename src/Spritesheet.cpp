#include "Spritesheet.h"
#include "debug.h"
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>

void Spritesheet::Create(std::string file) {
  std::string texture_path = file + ".png";
  std::string json_path = file + ".json";

  m_Texture = std::make_unique<Texture>("./assets/spritesheets/main.png", true);

  // IMPROVEMENT: Check json validity.
  LoadJsonInfo(json_path);
}

void Spritesheet::LoadJsonInfo(const std::string& json_path) {
  glm::ivec2 texture_size = m_Texture->GetSize();

  // Create the sprites base on the json.
  std::ifstream i(json_path);
  nlohmann::json j;
  i >> j;

  auto frames = j["frames"];

  if (frames.empty()) {
    PANIC("Spritesheet json is missing the 'frames' key");
  }

  for (auto& it : frames) {
    auto frame = it;
    auto filename = frame["filename"].get<std::string>();

    auto position = frame["frame"];
    int x = position["x"].get<int>();
    int y = position["y"].get<int>();
    int width = position["w"].get<int>();
    int height = position["h"].get<int>();

    if (x < 0 || x + width > texture_size.x || y < 0 || y + height > texture_size.y) {
      PANIC("The sprite '%s' defined in the json spritesheet has a wrong positioning\n",
            filename.c_str());
    }

    m_Sprites.insert({filename, Sprite(m_Texture.get(), x, y, width, height)});
  }
}

const Sprite& Spritesheet::GetSprite(const std::string& sprite_name) {
  return m_Sprites.at(sprite_name);
}
