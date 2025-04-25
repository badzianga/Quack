#include "Quack/Scene/Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 Transform::getForward() const {
    float pitch = glm::radians(rotation.x);
    float yaw = glm::radians(rotation.y);
    glm::vec3 forward;
    forward.x = std::sin(yaw) * std::cos(pitch);
    forward.y = std::sin(pitch);
    forward.z = -std::cos(yaw) * std::cos(pitch);
    return glm::normalize(forward);
}

glm::vec3 Transform::getRight() const {
    return glm::normalize(glm::cross(getForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 Transform::getUp() const {
    return glm::normalize(glm::cross(getRight(), getForward()));
}
