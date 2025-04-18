#include "Quack/Scene/TransformComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

void TransformComponent::start() {}

void TransformComponent::update() {}

glm::vec3 TransformComponent::getForward() const {
    float pitch = glm::radians(rotation.x);
    float yaw = glm::radians(rotation.y);
    glm::vec3 forward;
    forward.x = std::sin(yaw) * std::cos(pitch);
    forward.y = std::sin(pitch);
    forward.z = -std::cos(yaw) * std::cos(pitch);
    return glm::normalize(forward);
}

glm::vec3 TransformComponent::getRight() const {
    return glm::normalize(glm::cross(getForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 TransformComponent::getUp() const {
    return glm::normalize(glm::cross(getRight(), getForward()));
}
