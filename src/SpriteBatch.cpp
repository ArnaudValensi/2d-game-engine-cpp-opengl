//
// Created by Arnaud Valensi on 11/02/2020.
//

#include "SpriteBatch.h"
#include "Camera.h"
#include "CubeMeshBuilder.h"
#include "Mesh.h"
#include "QuadMeshBuilder.h"
#include "Shader.h"
#include "Texture.h"
#include "debug.h"
#include <GL/gl3w.h>

static Shader s_Shader;
static Mesh* s_Mesh;
static Camera* s_Camera;

void SpriteBatch::Init(Camera& camera) {
  s_Camera = &camera;
  s_Mesh = QuadMeshBuilder::BuildMesh();
  // s_Mesh = CubeMeshBuilder::BuildMesh();

  std::string vertex_shader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;

        out vec2 TexCoord;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        uniform vec2 tiling;
        uniform vec2 offset;

        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            TexCoord = aTexCoord * tiling + offset;
        }
    )";

  std::string fragment_shader = R"(
        #version 330 core
        out vec4 FragColor;

        in vec2 TexCoord;

        uniform sampler2D ourTexture;

        void main()
        {
            FragColor = texture(ourTexture, TexCoord);
        }
    )";

  s_Shader.Compile(vertex_shader.c_str(), fragment_shader.c_str(), nullptr);
}

// Draws the texture using the texture's width and height.
void SpriteBatch::Draw(Texture& texture, glm::vec2 position) {
  GL(glActiveTexture(GL_TEXTURE0));
  texture.Bind();
  s_Shader.Use();

  glm::vec2 texture_size = texture.GetSize();
  glm::vec2 model_scale = texture_size / (float) PIXELS_PER_UNIT;

  // https://learnopengl.com/Getting-started/Coordinate-Systems
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));
  model = glm::scale(model, glm::vec3(model_scale, 1.0f));

  glm::mat4 view = s_Camera->GetViewMatrix();
  glm::mat4 projection = s_Camera->GetProjectionMatrix();

  s_Shader.SetMatrix4("model", model);
  s_Shader.SetMatrix4("view", view);
  s_Shader.SetMatrix4("projection", projection);
  s_Shader.SetVector2f("tiling", {1.0, 1.0});

  s_Mesh->Draw(false);
}

void SpriteBatch::Draw(const Sprite& sprite, glm::vec3 position) const {
  const Texture& texture = sprite.GetTexture();
  const Rect sprite_rect = sprite.GetRect();

  GL(glActiveTexture(GL_TEXTURE0));
  texture.Bind();
  s_Shader.Use();

  // Sizes and positions are in pixels.
  glm::vec2 texture_size = texture.GetSize();
  glm::vec2 sprite_size = sprite_rect.Size();
  glm::vec2 sprite_position = sprite_rect.Position();

  glm::vec2 model_scale = sprite_size / (float) PIXELS_PER_UNIT;
  glm::vec2 tiling = sprite_size / texture_size;
  glm::vec2 offset = sprite_position / texture_size;

  // https://learnopengl.com/Getting-started/Coordinate-Systems
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, position);
  model = glm::scale(model, glm::vec3(model_scale, 1.0f));

  glm::mat4 view = s_Camera->GetViewMatrix();
  glm::mat4 projection = s_Camera->GetProjectionMatrix();

  s_Shader.SetMatrix4("model", model);
  s_Shader.SetMatrix4("view", view);
  s_Shader.SetMatrix4("projection", projection);
  s_Shader.SetVector2f("tiling", tiling);
  s_Shader.SetVector2f("offset", offset);

  s_Mesh->Draw(false);
}
