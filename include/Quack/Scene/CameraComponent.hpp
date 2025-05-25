#ifndef QUACK_CAMERA_COMPONENT_HPP
#define QUACK_CAMERA_COMPONENT_HPP
#include "Quack/Scene/Component.hpp"
#include "Quack/Math/Matrix4.hpp"

/**
 * @brief %Component that defines a camera for rendering the scene.
 *
 * Calculates view and projection matrices used for 3D rendering.
 * Should be attached to a GameObject that represents the camera in the scene.
 */
class CameraComponent final : public Component {
public:
    /// Enumeration with camera projection types.
    enum class ProjectionType { Perspective, Orthographic };

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
    [[nodiscard]] Matrix4 getViewMatrix() const;

    /**
     * @brief Calculate the projection matrix.
     *
     * @return Matrix representing the perspective or orthographic projection,
     * depending on selected projectionType.
     */
    [[nodiscard]] Matrix4 getProjectionMatrix() const;

    /**
     * @brief Return the combined projection and view matrix.
     *
     * Useful for shaders and camera-based calculations.
     *
     * @return Result matrix from projection and view multiplication.
     */
    [[nodiscard]] Matrix4 getProjectionViewMatrix() const;

    /**
     * @brief Get the statically stored projection-view matrix.
     *
     * This is shared across the application (e.g., for global rendering).
     * TODO: Calculated only by one active camera.
     *
     * @return Multiplied Projection-view matrix.
     */
    [[nodiscard]] static Matrix4 getStaticProjectionView();

    [[nodiscard]] static Vector3 getStaticPosition();

    nlohmann::json serialize() override;

    void deserialize(const nlohmann::json& json) override;

    /// Projection type of the camera.
    ProjectionType projectionType = ProjectionType::Perspective;

    /// Field of view in degrees.
    float fieldOfView = 45.f;

    /// Near clipping plane distance.
    float nearClip = 0.3f;

    /// Far clipping plane distance.
    float farClip = 1000.f;

    /// Aspect ratio of the camera's viewport (width / height).
    float aspectRatio = 4.f / 3.f;

    /// Orthogonal size used by Orthographic camera.
    float orthoSize = 5.0f;
private:
    static Matrix4 s_projectionView;
    static Vector3 s_position;
};

#endif //QUACK_CAMERA_COMPONENT_HPP
