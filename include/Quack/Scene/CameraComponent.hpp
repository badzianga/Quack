#ifndef QUACK_CAMERA_COMPONENT_HPP
#define QUACK_CAMERA_COMPONENT_HPP
#include "Quack/Scene/Component.hpp"
#include <glm/mat4x4.hpp>

class CameraComponent final : public Component {
public:
    void start() override;
    void update() override;

    [[nodiscard]] glm::mat4 getViewMatrix() const;
    [[nodiscard]] glm::mat4 getProjectionMatrix() const;
    [[nodiscard]] glm::mat4 getProjectionViewMatrix() const;
    [[nodiscard]] static glm::mat4 getStaticProjectionView();

    float fieldOfView = 60.f;
    float nearClip = 0.3f;
    float farClip = 1000.f;
    float aspectRatio = 4.f / 3.f;
private:
    static glm::mat4 s_projectionView;
};

#endif //QUACK_CAMERA_COMPONENT_HPP
