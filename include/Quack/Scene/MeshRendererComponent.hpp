#ifndef QUACK_MESH_RENDERER_COMPONENT_HPP
#define QUACK_MESH_RENDERER_COMPONENT_HPP
#include "Quack/Graphics.hpp"
#include "Quack/Scene/Component.hpp"
#include "Quack/Scene/Transform.hpp"

/**
 * @brief %Component responsible for rendering a 3D mesh.
 *
 * Uses a Mesh, Shader, and Material to draw an object in the scene.
 * Requires the GameObject to have a TransformComponent attached,
 * which should be available by default.
 */
class MeshRendererComponent final : public Component {
public:
    /**
     * @brief Initialize the renderer component.
     *
     * For now, it does nothing.
     */
    void start() override;

    /**
     * @brief Update the renderer each frame.
     *
     * Handles the rendering of the mesh using the assigned shader and material.
     */
    void update() override;

    /// The mesh to be rendered.
    Mesh mesh;

    /// The shader used to render the mesh.
    Shader shader;

    /// The material containing uniforms.
    Material material;
private:
    /**
     * @brief Compute the model matrix based on a TransformComponent.
     *
     * Combines translation, rotation, and scale into a single matrix.
     *
     * @param transform Pointer to the TransformComponent.
     * @return The resulting model matrix.
     */
    static glm::mat4 getModelMatrix(const Transform& transform);
};

#endif //QUACK_MESH_RENDERER_COMPONENT_HPP
