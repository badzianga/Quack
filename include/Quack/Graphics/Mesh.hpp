#ifndef QUACK_MESH_HPP
#define QUACK_MESH_HPP
#include "Quack/Graphics/Vertex.hpp"
#include "Quack/Graphics/Shader.hpp"
#include <cstdint>
#include <initializer_list>
#include <vector>

class Mesh {
public:
    Mesh();
    ~Mesh() = default;

    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) = delete;

    bool create(std::initializer_list<Vertex> vertices, std::initializer_list<uint32_t> indices);
    bool destroy();
    void draw(const Shader& shader) const;
private:
    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;
    uint32_t m_vao;
    uint32_t m_vbo;
    uint32_t m_ebo;

};

#endif //QUACK_MESH_HPP
