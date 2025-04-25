#ifndef QUACK_TRANSFORM_HPP
#define QUACK_TRANSFORM_HPP
#include <glm/mat4x4.hpp>

/**
 * @brief Class representing the position, rotation, and scale of a %GameObject.
 *
 * This pseudo-component is essential for spatial transformations and orientation in the 3D world.
 * It is added to every created GameObject by default.
 */
class Transform {
public:
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

#endif //QUACK_TRANSFORM_HPP
