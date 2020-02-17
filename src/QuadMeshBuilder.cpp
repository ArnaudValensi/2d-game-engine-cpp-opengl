//
// Created by Arnaud Valensi on 12/02/2020.
//

#include "QuadMeshBuilder.h"

Mesh* QuadMeshBuilder::BuildMesh() {
    std::vector<Vertex> vertices;

    // Top left.
    vertices.emplace_back(Vertex{{-0.5, 0.5, 0.0},
                                 {0.0, 1.0}});
    // Top right.
    vertices.emplace_back(Vertex{{0.5, 0.5, 0.0},
                                 {1.0, 1.0}});
    // Bottom right.
    vertices.emplace_back(Vertex{{0.5, -0.5, 0.0},
                                 {1.0, 0.0}});
    // Bottom left.
    vertices.emplace_back(Vertex{{-0.5, -0.5, 0.0},
                                 {0.0, 0.0}});

    int vertices_count = vertices.size();
    std::vector<uint32_t> indices;
    indices.emplace_back(vertices_count - 4);
    indices.emplace_back(vertices_count - 3);
    indices.emplace_back(vertices_count - 2);
    indices.emplace_back(vertices_count - 4);
    indices.emplace_back(vertices_count - 2);
    indices.emplace_back(vertices_count - 1);

    return new Mesh(vertices, indices);
}
