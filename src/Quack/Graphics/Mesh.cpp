#include "Quack/Graphics/Mesh.hpp"
#include "Quack/Utils/Logger.hpp"
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
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

bool Mesh::create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
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
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, normal))
    );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,
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
            { { -0.5f, 0.f,  0.5f }, { 0.f, 1.f, 0.f }, { 0.f, 0.f } },
            { {  0.5f, 0.f,  0.5f }, { 0.f, 1.f, 0.f }, { 1.f, 0.f } },
            { {  0.5f, 0.f, -0.5f }, { 0.f, 1.f, 0.f }, { 1.f, 1.f } },
            { { -0.5f, 0.f, -0.5f }, { 0.f, 1.f, 0.f }, { 0.f, 1.f } },
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
            // Front face
            {{-0.5f, -0.5f,  0.5f}, { 0.f, 0.f, 1.f }, {0.f, 0.f}},
            {{ 0.5f, -0.5f,  0.5f}, { 0.f, 0.f, 1.f }, {1.f, 0.f}},
            {{ 0.5f,  0.5f,  0.5f}, { 0.f, 0.f, 1.f }, {1.f, 1.f}},
            {{-0.5f,  0.5f,  0.5f}, { 0.f, 0.f, 1.f }, {0.f, 1.f}},

            // Back face
            {{ 0.5f, -0.5f, -0.5f}, { 0.f, 0.f, -1.f }, {0.f, 0.f}},
            {{-0.5f, -0.5f, -0.5f}, { 0.f, 0.f, -1.f }, {1.f, 0.f}},
            {{-0.5f,  0.5f, -0.5f}, { 0.f, 0.f, -1.f }, {1.f, 1.f}},
            {{ 0.5f,  0.5f, -0.5f}, { 0.f, 0.f, -1.f }, {0.f, 1.f}},

            // Left face
            {{-0.5f, -0.5f, -0.5f}, { -1.f, 0.f, 0.f }, {0.f, 0.f}},
            {{-0.5f, -0.5f,  0.5f}, { -1.f, 0.f, 0.f }, {1.f, 0.f}},
            {{-0.5f,  0.5f,  0.5f}, { -1.f, 0.f, 0.f }, {1.f, 1.f}},
            {{-0.5f,  0.5f, -0.5f}, { -1.f, 0.f, 0.f }, {0.f, 1.f}},

            // Right face
            {{ 0.5f, -0.5f,  0.5f}, { 1.f, 0.f, 0.f }, {0.f, 0.f}},
            {{ 0.5f, -0.5f, -0.5f}, { 1.f, 0.f, 0.f }, {1.f, 0.f}},
            {{ 0.5f,  0.5f, -0.5f}, { 1.f, 0.f, 0.f }, {1.f, 1.f}},
            {{ 0.5f,  0.5f,  0.5f}, { 1.f, 0.f, 0.f }, {0.f, 1.f}},

            // Top face
            {{-0.5f,  0.5f, -0.5f}, { 0.f, 1.f, 0.f }, {0.f, 1.f}},
            {{ 0.5f,  0.5f, -0.5f}, { 0.f, 1.f, 0.f }, {1.f, 1.f}},
            {{ 0.5f,  0.5f,  0.5f}, { 0.f, 1.f, 0.f }, {1.f, 0.f}},
            {{-0.5f,  0.5f,  0.5f}, { 0.f, 1.f, 0.f }, {0.f, 0.f}},

            // Bottom face
            {{-0.5f, -0.5f,  0.5f}, { 0.f, -1.f, 0.f }, {0.f, 0.f}},
            {{ 0.5f, -0.5f,  0.5f}, { 0.f, -1.f, 0.f }, {1.f, 0.f}},
            {{ 0.5f, -0.5f, -0.5f}, { 0.f, -1.f, 0.f }, {1.f, 1.f}},
            {{-0.5f, -0.5f, -0.5f}, { 0.f, -1.f, 0.f }, {0.f, 1.f}},
        },
        {
            0,  1,  2,  2,  3,  0,   // Front face
            4,  5,  6,  6,  7,  4,   // Back face
            8,  9,  10, 10, 11, 8,   // Left face
            12, 13, 14, 14, 15, 12,  // Right face
            16, 17, 18, 18, 19, 16,  // Top face
            20, 21, 22, 22, 23, 20,  // Bottom face
        }
    );

    return mesh;
}

Mesh Mesh::createSphere() {
    constexpr int stackCount = 18;
    constexpr int sectorCount = 36;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    for (int i = 0; i <= stackCount; ++i) {
        float stackAngle = M_PI / 2.f - i * (M_PI / stackCount); // from +pi/2 to -pi/2
        float xy = 0.5f * std::cos(stackAngle);
        float z = 0.5f * std::sin(stackAngle);

        for (int j = 0; j <= sectorCount; ++j) {
            float sectorAngle = static_cast<float>(j) * (2.f * static_cast<float>(M_PI) / sectorCount); // from 0 to 2pi

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            glm::vec3 position = glm::vec3(x, y, z);
            glm::vec3 normal = glm::normalize(position);
            glm::vec2 texCoord = glm::vec2(
                static_cast<float>(j) / sectorCount,
                static_cast<float>(i) / stackCount
            );

            vertices.push_back(Vertex{position, normal, texCoord});
        }
    }

    for (uint32_t i = 0; i < stackCount; ++i) {
        for (uint32_t j = 0; j < sectorCount; ++j) {
            uint32_t first = i * (sectorCount + 1) + j;
            uint32_t second = first + sectorCount + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    Mesh mesh;
    mesh.create(vertices, indices);
    return mesh;
}


Mesh Mesh::loadObj(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        Logger::error("Failed to load file: " + std::string(filename));
        return {};
    }

    std::vector<glm::vec3> tempPositions;
    std::vector<glm::vec2> tempTexCoords;
    std::vector<glm::vec3> tempNormals;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            glm::vec3 pos;
            iss >> pos.x >> pos.y >> pos.z;
            tempPositions.push_back(pos);
        }
        else if (prefix == "vt") {
            glm::vec2 texCoord;
            iss >> texCoord.x >> texCoord.y;
            tempTexCoords.push_back(texCoord);
        }
        else if (prefix == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        }
        else if (prefix == "f") {
            std::string vertexStr;
            for (int i = 0; i < 3; ++i) {
                iss >> vertexStr;
                size_t slash1 = vertexStr.find('/');
                size_t slash2 = vertexStr.find('/', slash1 + 1);
                int posIndex = std::stoi(vertexStr.substr(0, slash1)) - 1;
                int texCoordIndex = std::stoi(vertexStr.substr(slash1 +1, slash2 - slash1 - 1)) - 1;
                int normalIndex = std::stoi(vertexStr.substr(slash2 + 1)) - 1;

                Vertex vertex{
                    .position = tempPositions[posIndex],
                    .normal = tempNormals[normalIndex],
                    .texCoord = tempTexCoords[texCoordIndex],
                };

                vertices.push_back(vertex);
                indices.push_back(static_cast<uint32_t>(vertices.size() - 1));
            }
        }
    }
    file.close();

    Mesh mesh;
    mesh.create(vertices, indices);
    return mesh;
}
