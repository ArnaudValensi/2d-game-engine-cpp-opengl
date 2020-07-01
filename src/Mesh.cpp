//
// Created by Arnaud Valensi on 12/02/2020.
//

#include "Mesh.h"
#include "debug.h"
#include <GL/gl3w.h>
#include <utility>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
    : m_Vertices(std::move(vertices)), m_Indices(std::move(indices)) {
  GL(glGenVertexArrays(1, &m_VA));
  GL(glBindVertexArray(m_VA));

  GL(glGenBuffers(1, &m_VB));
  GL(glBindBuffer(GL_ARRAY_BUFFER, m_VB));
  GL(glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW));

  GL(glGenBuffers(1, &m_IB));
  GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB));
  GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(uint32_t), &m_Indices[0], GL_STATIC_DRAW));

  GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position)));
  GL(glEnableVertexAttribArray(0));

  GL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv)));
  GL(glEnableVertexAttribArray(1));

  GL(glBindVertexArray(0));
  GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
  GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void Mesh::Draw(bool wireframe) {
  GL(glBindVertexArray(m_VA));

  if (wireframe) {
    GL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
  }

  GL(glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0));

  if (wireframe) {
    GL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
  }
}
