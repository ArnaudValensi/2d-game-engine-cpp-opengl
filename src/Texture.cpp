//
// Created by Arnaud Valensi on 12/02/2020.
//

#include "Texture.h"
#include "debug.h"

#define STB_IMAGE_IMPLEMENTATION

#include <GL/gl3w.h>
#include <fmt/core.h>
#include <stb_image.h>

Texture::Texture(const char* file_path, bool has_alpha) {
  GL(glGenTextures(1, &m_TextureId));
  GL(glBindTexture(GL_TEXTURE_2D, m_TextureId));

  GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
  GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
  GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

  int channels_count;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(file_path, &m_Size.x, &m_Size.y, &channels_count, 0);
  if (data == NULL) {
    PANIC("Cannot load image");
  }

  GLint format = has_alpha ? GL_RGBA : GL_RGB;

  GL(glTexImage2D(GL_TEXTURE_2D, 0, format, m_Size.x, m_Size.y, 0, format, GL_UNSIGNED_BYTE, data));
  GL(glBindTexture(GL_TEXTURE_2D, 0));

  fmt::print("width: {}, height: {} channels: {}\n", m_Size.x, m_Size.y, channels_count);

  stbi_image_free(data);
}

Texture::~Texture() {
  GL(glDeleteTextures(1, &m_TextureId));
}

void Texture::Bind() const {
  GL(glBindTexture(GL_TEXTURE_2D, m_TextureId));
}

glm::ivec2 Texture::GetSize() const {
  return m_Size;
}
