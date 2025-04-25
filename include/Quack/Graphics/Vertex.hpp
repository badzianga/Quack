#ifndef QUACK_VERTEX_HPP
#define QUACK_VERTEX_HPP
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

/**
 * @brief Representation of a single vertex in 3D space.
 *
 * This struct is used to define the geometry of a mesh. It currently includes
 * only the position of the vertex, but will be extended to support normals,
 * texture coordinates, tangents, etc.
 */
struct Vertex {
    /**
     * @brief Position of the vertex in 3D space.
     *
     * This is the primary attribute used for rendering the mesh.
     */
    glm::vec3 position;

    /**
     * @brief Normal direction of the vertex.
     */
    glm::vec3 normal;

    /**
     * @brief Texture UV of the vertex.
     */
    glm::vec2 texCoord;
};

#endif //QUACK_VERTEX_HPP
