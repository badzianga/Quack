#ifndef QUACK_CAMERA_COMPONENT_HPP
#define QUACK_CAMERA_COMPONENT_HPP
#include "Quack/Scene/Component.hpp"
#include <glm/mat4x4.hpp>

/**
 * @brief %Component that defines a camera for rendering the scene.
 *
 * Calculates view and projection matrices used for 3D rendering.
 * Should be attached to a GameObject that represents the camera in the scene.
 */
class CameraComponent final : public Component {
public:
    /**
     * @brief Initialize the camera component.
     *
     * Called once when the component is first activated.
     */
    void start() override;

    /**
     * @brief Update the camera component each frame.
     *
     * Updates internal camera matrices, TODO: if needed.
     */
    void update() override;

    /**
     * @brief Calculate the view matrix based on the camera's
     * position and orientation.
     *
     * @return Matrix representing the view transformation.
     */
    [[nodiscard]] glm::mat4 getViewMatrix() const;

    /**
     * @brief Calculate the projection matrix.
     *
     * @return Matrix representing the perspective projection.
     */
    [[nodiscard]] glm::mat4 getProjectionMatrix() const;

    /**
     * @brief Return the combined projection and view matrix.
     *
     * Useful for shaders and camera-based calculations.
     *
     * @return Result matrix from projection and view multiplication.
     */
    [[nodiscard]] glm::mat4 getProjectionViewMatrix() const;

    /**
     * @brief Get the statically stored projection-view matrix.
     *
     * This is shared across the application (e.g., for global rendering).
     * TODO: Calculated only by one active camera.
     *
     * @return Multiplied Projection-view matrix.
     */
    [[nodiscard]] static glm::mat4 getStaticProjectionView();

    /// Field of view in degrees.
    float fieldOfView = 60.f;

    /// Near clipping plane distance.
    float nearClip = 0.3f;

    /// Far clipping plane distance.
    float farClip = 1000.f;

    /// Aspect ratio of the camera's viewport (width / height).
    float aspectRatio = 4.f / 3.f;
private:
    static glm::mat4 s_projectionView;
};

#endif //QUACK_CAMERA_COMPONENT_HPP
