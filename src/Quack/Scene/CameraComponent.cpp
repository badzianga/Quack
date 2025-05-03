#include "Quack/Math/Math.hpp"
#include "Quack/Math/Matrix4.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 CameraComponent::s_projectionView{1.f};

void CameraComponent::start() {}

void CameraComponent::update() {
    if (!enabled) return;

    s_projectionView = getProjectionViewMatrix();
}

glm::mat4 CameraComponent::getViewMatrix() const {
    Vector3 position = gameObject->transform.position;
    Vector3 forward = gameObject->transform.getForward();
    Vector3 up = gameObject->transform.getUp();

    Matrix4 result = Math::lookAt(position, position + forward, up);
    return reinterpret_cast<glm::mat4&>(result);
}

glm::mat4 CameraComponent::getProjectionMatrix() const {
    if (projectionType == ProjectionType::Perspective) {
        return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClip, farClip);
    }
    const float halfHeight = orthoSize * 0.5f;
    const float halfWidth = halfHeight * aspectRatio;
    return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearClip, farClip);
}

glm::mat4 CameraComponent::getProjectionViewMatrix() const {
    return getProjectionMatrix() * getViewMatrix();
}

glm::mat4 CameraComponent::getStaticProjectionView() {
    return s_projectionView;
}
