#pragma once

#include "Sprite.h"
#include "Texture.h"
#include <map>
#include <string>

class Sprite;
class Renderer;

class Spritesheet {
private:
  std::map<std::string, Sprite> m_Sprites;
  std::unique_ptr<Texture> m_Texture;

  void LoadJsonInfo(const std::string& json_path);

public:
  void Create(std::string file);
  [[nodiscard]] const Sprite& GetSprite(const std::string& sprite_name);
};
