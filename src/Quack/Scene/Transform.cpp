#include "Quack/Scene/Transform.hpp"
#include "Quack/Math/Math.hpp"
#include <cmath>

Vector3 Transform::getForward() const {
    float pitch = Math::toRadians(rotation.x);
    float yaw = Math::toRadians(rotation.y);
    Vector3 forward;
    forward.x = std::sin(yaw) * std::cos(pitch);
    forward.y = std::sin(pitch);
    forward.z = -std::cos(yaw) * std::cos(pitch);
    return forward.normalized();
}

Vector3 Transform::getRight() const {
    return Vector3::cross(getForward(), { 0.f, 1.f, 0.f }).normalized();
}

Vector3 Transform::getUp() const {
    return Vector3::cross(getRight(), getForward()).normalized();
}
