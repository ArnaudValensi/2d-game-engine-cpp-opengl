//
// Created by Arnaud Valensi on 12/02/2020.
//

#pragma once


#include <GL/gl3w.h>
#include <glm/vec2.hpp>

class Texture {
private:
    GLuint m_TextureId;
    glm::ivec2 m_Size;

public:
    explicit Texture(const char* file_path, bool has_alpha);
    void Bind() const;
    [[nodiscard]] glm::ivec2 GetSize() const;
    virtual ~Texture();
};


