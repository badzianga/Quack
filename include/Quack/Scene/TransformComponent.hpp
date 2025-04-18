#ifndef QUACK_TRANSFORM_COMPONENT_HPP
#define QUACK_TRANSFORM_COMPONENT_HPP
#include "Quack/Scene/Component.hpp"
#include <glm/mat4x4.hpp>

/**
 * @brief %Component representing the position, rotation, and scale of a %GameObject.
 *
 * This component is essential for spatial transformations and orientation in the 3D world.
 * It is added to every created GameObject by default.
 */
class TransformComponent final : public Component {
public:
    /**
     * @brief Call once when the component is initialized.
     *
     * In the future it will be used to perform any setup required
     * for the transform component. For now, it does nothing.
     */
    void start() override;

    /**
     * @brief Call every frame to update the component.
     *
     * Can be used to apply continuous transformations,
     * but in the future. For now, it does nothing.
     */
    void update() override;

    /**
     * @brief Get the forward direction vector.
     *
     * Calculated from the current rotation.
     * With rotation (0, 0, 0), forward direction is to the negative Z axis (0, 0, -1).
     *
     * @return 3D vector with normalized forward direction.
     */
    [[nodiscard]] glm::vec3 getForward() const;

    /**
     * @brief Get the right direction vector.
     *
     * Calculated from the current rotation.
     *
     * @return 3D vector with normalized right direction.
     */
    [[nodiscard]] glm::vec3 getRight() const;

    /**
     * @brief Get the up direction vector.
     *
     * Calculated from the current rotation.
     *
     * @return 3D vector with normalized up direction.
     */
    [[nodiscard]] glm::vec3 getUp() const;

    /// Position of the GameObject in world space.
    glm::vec3 position{0.f};

    /// Rotation of the GameObject in Euler angles (degrees).
    glm::vec3 rotation{0.f};

    /// Scale of the GameObject.
    glm::vec3 scale{1.f};
};

#endif //QUACK_TRANSFORM_COMPONENT_HPP
