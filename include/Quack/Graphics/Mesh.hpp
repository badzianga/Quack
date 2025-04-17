#ifndef QUACK_MESH_HPP
#define QUACK_MESH_HPP
#include "Quack/Graphics/Vertex.hpp"
#include <cstdint>
#include <initializer_list>
#include <vector>

/**
 * @brief Representation of a 3D mesh.
 *
 * A mesh is composed of vertices and indices that define its shape. This class
 * handles the creation, destruction, and drawing of the mesh in OpenGL.
 */
class Mesh {
public:
    /**
     * @brief Default constructor.
     *
     * This constructor doesn't actually create the mesh,
     * it is used only to declare the object.
     */
    Mesh();

    /**
     * @brief Destructor.
     *
     * Cleans up the mesh's resources, including the OpenGL buffers.
     */
    ~Mesh();

    /**
     * @brief Deleted copy constructor.
     *
     * Mesh objects cannot be copied.
     */
    Mesh(const Mesh&) = delete;

    /**
     * @brief Move constructor.
     *
     * Transfers the resources of another mesh to this one.
     *
     * @param other The mesh to move from.
     */
    Mesh(Mesh&& other) noexcept;

    /**
     * @brief Deleted copy assignment.
     *
     * Mesh objects cannot be copied.
     */
    Mesh& operator=(const Mesh&) = delete;

    /**
     * @brief Move assignment operator.
     *
     * Transfers the resources of another mesh to this one using assignment.
     *
     * @param other The mesh to move from.
     * @return Reference to the current mesh.
     */
    Mesh& operator=(Mesh&& other) noexcept;

    /**
     * @brief Create a mesh from a list of vertices and indices.
     *
     * This function initializes the OpenGL buffers (VAO, VBO, EBO) with the
     * provided vertices and indices.
     *
     * @param vertices The list of vertices defining the mesh geometry.
     * @param indices The list of indices for indexed drawing.
     * @return True if the mesh was successfully created, false otherwise.
     */
    bool create(std::initializer_list<Vertex> vertices, std::initializer_list<uint32_t> indices);

    /**
     * @brief Destroy the mesh and clean up OpenGL resources.
     *
     * Frees the VAO, VBO, and EBO associated with this mesh.
     *
     * @return True if the mesh was successfully destroyed, false otherwise.
     */
    bool destroy();

    /**
     * @brief Draws the mesh using the assigned OpenGL buffers.
     *
     * This function binds the necessary buffers and draws the mesh using OpenGL.
     */
    void draw() const;

    /**
     * @brief Create a default cube mesh.
     *
     * Generates a unit cube mesh, typically used for basic object representation.
     *
     * @return The generated cube mesh.
     */
    static Mesh createCube();

    /**
     * @brief Create a default plane mesh.
     *
     * Generates a flat XZ plane mesh, typically used for floors or other flat surfaces.
     *
     * @return The generated plane mesh.
     */
    static Mesh createPlane();
private:
    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;
    uint32_t m_vao;
    uint32_t m_vbo;
    uint32_t m_ebo;
};

#endif //QUACK_MESH_HPP
