#ifndef QUACK_TRANSFORM_HPP
#define QUACK_TRANSFORM_HPP
#include "Quack/Scene/IJsonSerializable.hpp"
#include "Quack/Math/Vector3.hpp"

/**
 * @brief Class representing the position, rotation, and scale of a %GameObject.
 *
 * This pseudo-component is essential for spatial transformations and orientation in the 3D world.
 * It is added to every created GameObject by default.
 */
class Transform : public IJsonSerializable {
public:
    /**
     * @brief Get the forward direction vector.
     *
     * Calculated from the current rotation.
     * With rotation (0, 0, 0), forward direction is to the negative Z axis (0, 0, -1).
     *
     * @return 3D vector with normalized forward direction.
     */
    [[nodiscard]] Vector3 getForward() const;

    /**
     * @brief Get the right direction vector.
     *
     * Calculated from the current rotation.
     *
     * @return 3D vector with normalized right direction.
     */
    [[nodiscard]] Vector3 getRight() const;

    /**
     * @brief Get the up direction vector.
     *
     * Calculated from the current rotation.
     *
     * @return 3D vector with normalized up direction.
     */
    [[nodiscard]] Vector3 getUp() const;

    nlohmann::json serialize() override;

    void deserialize(const nlohmann::json& json) override;

    /// Position of the GameObject in world space.
    Vector3 position{0.f};

    /// Rotation of the GameObject in Euler angles (degrees).
    Vector3 rotation{0.f};

    /// Scale of the GameObject.
    Vector3 scale{1.f};
};

#endif //QUACK_TRANSFORM_HPP
