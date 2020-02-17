//
// Created by Arnaud Valensi on 13/02/2020.
//

#pragma once


#include "Rect.h"
#include "Texture.h"
#include "debug.h"

class Sprite {
private:
    Texture* m_Texture;
    Rect m_Rect;

public:
    Sprite(Texture* texture, int x, int y, int width, int height);
    [[nodiscard]] const Texture& GetTexture() const;
    [[nodiscard]] Rect GetRect() const;
};


