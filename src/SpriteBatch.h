//
// Created by Arnaud Valensi on 11/02/2020.
//

#pragma once


#include "Camera.h"
#include "Texture.h"
#include "Sprite.h"

class SpriteBatch {
public:
    void Init(Camera& camera);
    void Draw(Texture& texture, glm::vec2 position);
    void Draw(const Sprite& sprite, glm::vec3 position) const;
};


