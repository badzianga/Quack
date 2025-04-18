#include "Quack/Scene/TransformComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

void TransformComponent::start() {}

void TransformComponent::update() {}

glm::vec3 TransformComponent::getForward() const {
    // TODO: default camera front is to X axis instead of Z axis, how to change it?
    float radiansX = glm::radians(rotation.x);
    float radiansY = glm::radians(rotation.y);
    glm::vec3 forward;
    forward.x = std::cos(radiansY) * std::cos(radiansX);
    forward.y = std::sin(radiansX);
    forward.z = std::sin(radiansY) * std::cos(radiansX);
    return glm::normalize(forward);
}

glm::vec3 TransformComponent::getRight() const {
    return glm::normalize(glm::cross(getForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 TransformComponent::getUp() const {
    return glm::normalize(glm::cross(getRight(), getForward()));
}
