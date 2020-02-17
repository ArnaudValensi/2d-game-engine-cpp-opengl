//
// Created by Arnaud Valensi on 12/02/2020.
//

#include "CubeMeshBuilder.h"
#include "debug.h"

namespace Direction {
    enum Type {
        North,
        East,
        South,
        West,
        Up,
        Down
    };

    static const Type All[] = {
            North,
            East,
            South,
            West,
            Up,
            Down
    };
}

static void s_CreateQuad(Direction::Type direction, std::vector<Vertex>& vertices) {
    glm::vec3 pos = {0, 0, 0};
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;

    switch (direction) {
        case Direction::Type::North:
            v0 = {pos.x + 0.5f, pos.y - 0.5f, pos.z - 0.5f};
            v1 = {pos.x + 0.5f, pos.y + 0.5f, pos.z - 0.5f};
            v2 = {pos.x - 0.5f, pos.y + 0.5f, pos.z - 0.5f};
            v3 = {pos.x - 0.5f, pos.y - 0.5f, pos.z - 0.5f};
            break;
        case Direction::Type::East:
            v0 = {pos.x + 0.5f, pos.y - 0.5f, pos.z + 0.5f};
            v1 = {pos.x + 0.5f, pos.y + 0.5f, pos.z + 0.5f};
            v2 = {pos.x + 0.5f, pos.y + 0.5f, pos.z - 0.5f};
            v3 = {pos.x + 0.5f, pos.y - 0.5f, pos.z - 0.5f};
            break;
        case Direction::Type::South:
            v0 = {pos.x - 0.5f, pos.y - 0.5f, pos.z + 0.5f};
            v1 = {pos.x - 0.5f, pos.y + 0.5f, pos.z + 0.5f};
            v2 = {pos.x + 0.5f, pos.y + 0.5f, pos.z + 0.5f};
            v3 = {pos.x + 0.5f, pos.y - 0.5f, pos.z + 0.5f};
            break;
        case Direction::Type::West:
            v0 = {pos.x - 0.5f, pos.y - 0.5f, pos.z - 0.5f};
            v1 = {pos.x - 0.5f, pos.y + 0.5f, pos.z - 0.5f};
            v2 = {pos.x - 0.5f, pos.y + 0.5f, pos.z + 0.5f};
            v3 = {pos.x - 0.5f, pos.y - 0.5f, pos.z + 0.5f};
            break;
        case Direction::Type::Up:
            v0 = {pos.x - 0.5f, pos.y + 0.5f, pos.z - 0.5f};
            v1 = {pos.x + 0.5f, pos.y + 0.5f, pos.z - 0.5f};
            v2 = {pos.x + 0.5f, pos.y + 0.5f, pos.z + 0.5f};
            v3 = {pos.x - 0.5f, pos.y + 0.5f, pos.z + 0.5f};
            break;
        case Direction::Down:
            v0 = {pos.x - 0.5f, pos.y - 0.5f, pos.z + 0.5f};
            v1 = {pos.x + 0.5f, pos.y - 0.5f, pos.z + 0.5f};
            v2 = {pos.x + 0.5f, pos.y - 0.5f, pos.z - 0.5f};
            v3 = {pos.x - 0.5f, pos.y - 0.5f, pos.z - 0.5f};
            break;
        default:
            PANIC("Bad direction");
    }

    vertices.emplace_back(Vertex{v0, {0.0, 1.0}});
    vertices.emplace_back(Vertex{v1, {1.0, 1.0}});
    vertices.emplace_back(Vertex{v2, {1.0, 0.0}});
    vertices.emplace_back(Vertex{v3, {0.0, 0.0}});
}

void s_AddQuadIndices(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    int vertices_count = vertices.size();

    indices.emplace_back(vertices_count - 4);
    indices.emplace_back(vertices_count - 3);
    indices.emplace_back(vertices_count - 2);
    indices.emplace_back(vertices_count - 4);
    indices.emplace_back(vertices_count - 2);
    indices.emplace_back(vertices_count - 1);
}

Mesh* CubeMeshBuilder::BuildMesh() {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    for (const auto direction : Direction::All) {
        s_CreateQuad(direction, vertices);
        s_AddQuadIndices(vertices, indices);
    }

    return new Mesh(vertices, indices);
}
