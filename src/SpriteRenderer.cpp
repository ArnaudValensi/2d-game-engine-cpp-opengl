//
// Created by Arnaud Valensi on 11/02/2020.
//

#include "SpriteRenderer.h"
#include "Texture.h"

void SpriteRenderer::Init() {
  // Configure VAO/VBO
  GLuint VBO;
  GLfloat vertices[] = {
    // Pos      // Tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f};

  glGenVertexArrays(1, &m_QuadVao);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(m_QuadVao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void SpriteRenderer::Draw(
  Shader& shader,
  Texture& texture,
  glm::vec2 position,
  glm::vec2 size,
  GLfloat rotate,
  glm::vec3 color) {
  // Prepare transformations
  shader.Use();
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));

  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  shader.SetMatrix4("model", model);
  shader.SetVector3f("spriteColor", color);

  glActiveTexture(GL_TEXTURE0);
  texture.Bind();

  glBindVertexArray(m_QuadVao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}
