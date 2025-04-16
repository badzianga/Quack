#include "Quack/Scene/TransformComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

void TransformComponent::start() {}

void TransformComponent::update() {}

glm::vec3 TransformComponent::getForward() const {
    glm::vec4 forward = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
    auto rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    forward = rotationMatrix * forward;
    return forward;
}

glm::vec3 TransformComponent::getRight() const {
    return glm::normalize(glm::cross(getForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 TransformComponent::getUp() const {
    return glm::normalize(glm::cross(getRight(), getForward()));
}
