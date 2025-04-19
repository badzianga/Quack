#include "Quack/Graphics/Mesh.hpp"
#include "Quack/Utils/Logger.hpp"
#include <glad/glad.h>
#include <utility>

Mesh::Mesh() : m_vao(0), m_vbo(0), m_ebo(0) {}

// TODO: probably called after GL context destruction
Mesh::~Mesh() {
    destroy();
}

Mesh::Mesh(Mesh&& other) noexcept
    : m_vao(std::exchange(other.m_vao, 0)),
      m_vbo(std::exchange(other.m_vbo, 0)),
      m_ebo(std::exchange(other.m_ebo, 0)) {

    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);

    other.m_vertices.clear();
    other.m_indices.clear();

    Logger::debug("Mesh object moved using constructor");
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    m_vao = std::exchange(other.m_vao, 0);
    m_vbo = std::exchange(other.m_vbo, 0);
    m_ebo = std::exchange(other.m_ebo, 0);

    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);

    other.m_vertices.clear();
    other.m_indices.clear();

    Logger::debug("Mesh object moved using assignment operator");
    return *this;
}

bool Mesh::create(std::initializer_list<Vertex> vertices, std::initializer_list<uint32_t> indices) {
    m_vertices = vertices;
    m_indices = indices;

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<int>(m_vertices.size() * sizeof(Vertex)),
        m_vertices.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<int>(m_indices.size() * sizeof(uint32_t)),
        m_indices.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, position))
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, texCoord))
    );

    glBindVertexArray(0);

    Logger::debug(
        "Mesh created with "
        + std::to_string(m_vertices.size())
        + " vertices and "
        + std::to_string(m_indices.size())
        + " indices"
    );

    return true;
}

bool Mesh::destroy() {
    glDeleteBuffers(1, &m_ebo);
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);

    m_vao = 0;
    m_vbo = 0;
    m_ebo = 0;

    Logger::debug("Mesh destroyed");

    return true;
}

void Mesh::draw() const {
    glBindVertexArray(m_vao);

    glDrawElements(GL_TRIANGLES, static_cast<int>(m_indices.size()), GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}

Mesh Mesh::createPlane() {
    Mesh mesh;

    mesh.create(
        {
            { { -0.5f, 0.f,  0.5f }, { 0.f, 0.f } },
            { {  0.5f, 0.f,  0.5f }, { 1.f, 0.f } },
            { {  0.5f, 0.f, -0.5f }, { 1.f, 1.f } },
            { { -0.5f, 0.f, -0.5f }, { 0.f, 1.f } },
        },
        {
            0, 1, 2,
            0, 2, 3,
        }
    );

    return mesh;
}

Mesh Mesh::createCube() {
    Mesh mesh;

    mesh.create(
        {
            {{-0.5f, -0.5f,  0.5f}, {0.f, 0.f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.f, 0.f}},
            {{ 0.5f,  0.5f,  0.5f}, {1.f, 1.f}},
            {{-0.5f,  0.5f,  0.5f}, {0.f, 1.f}},

            {{-0.5f, -0.5f, -0.5f}, {1.f, 0.f}},
            {{ 0.5f, -0.5f, -0.5f}, {0.f, 0.f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.f, 1.f}},
            {{-0.5f,  0.5f, -0.5f}, {1.f, 1.f}},
        },
        {
            0, 1, 2, 2, 3, 0,  // Front face
            1, 5, 6, 6, 2, 1,  // Right face
            5, 4, 7, 7, 6, 5,  // Back face
            4, 0, 3, 3, 7, 4,  // Left face
            3, 2, 6, 6, 7, 3,  // Top face
            4, 5, 1, 1, 0, 4,  // Bottom face
        }
    );

    return mesh;
}
