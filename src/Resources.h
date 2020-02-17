#pragma once


#include <vector>
#include "Sprite.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "Spritesheet.h"
#include "Tile.h"

class Resources {
public:
    enum class Sprites {
        Player = 0,
        Grass,
        DirtWall
    };

    enum class Tiles {
        Grass = 0,
        DirtWall
    };

private:
    std::map<Sprites, Sprite> m_Sprites;
    std::map<Tiles, Tile> m_Tiles;
    Spritesheet m_Spritesheet;

public:
    void Create();

    [[nodiscard]] const Sprite& GetSprite(Resources::Sprites sprite_enum) const;
    [[nodiscard]] const Tile& GetTile(Resources::Tiles tile_enum) const;
};


