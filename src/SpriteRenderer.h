//
// Created by Arnaud Valensi on 11/02/2020.
//

#pragma once


#include "Shader.h"
#include "Texture.h"

class SpriteRenderer {
public:
    void Init();
    void Draw(
            Shader& shader,
            Texture& texture,
            glm::vec2 position,
            glm::vec2 size,
            GLfloat rotate,
            glm::vec3 color
    );
private:
    GLuint m_QuadVao;
};


