#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/TransformComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 CameraComponent::s_projectionView{1.f};

void CameraComponent::start() {}

void CameraComponent::update() {
    s_projectionView = getProjectionViewMatrix();
}

glm::mat4 CameraComponent::getViewMatrix() const {
    auto transform = gameObject->getComponent<TransformComponent>();
    assert(transform != nullptr);
    const glm::vec3& position = transform->position;
    glm::vec3 forward = transform->getForward();
    glm::vec3 up = transform->getUp();

    return glm::lookAt(position, position + forward, up);
}

glm::mat4 CameraComponent::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClip, farClip);
}

glm::mat4 CameraComponent::getProjectionViewMatrix() const {
    return getProjectionMatrix() * getViewMatrix();
}

glm::mat4 CameraComponent::getStaticProjectionView() {
    return s_projectionView;
}
