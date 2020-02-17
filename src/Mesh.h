//
// Created by Arnaud Valensi on 12/02/2020.
//

#pragma once


#include <vector>
#include <GL/gl3w.h>
#include <glm/vec2.hpp>
#include "Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
};

class Mesh {
private:
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;
    GLuint m_VA;
    GLuint m_VB;
    GLuint m_IB;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
    void Draw(bool wireframe);
};


