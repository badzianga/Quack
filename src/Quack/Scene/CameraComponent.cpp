#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 CameraComponent::s_projectionView{1.f};

void CameraComponent::start() {}

void CameraComponent::update() {
    s_projectionView = getProjectionViewMatrix();
}

glm::mat4 CameraComponent::getViewMatrix() const {
    const glm::vec3& position = gameObject->transform.position;
    glm::vec3 forward = gameObject->transform.getForward();
    glm::vec3 up = gameObject->transform.getUp();

    return glm::lookAt(position, position + forward, up);
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
