#include "Quack/Scene/Transform.hpp"
#include "Quack/Math/Math.hpp"
#include <cmath>
#include <nlohmann/json.hpp>

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

nlohmann::json Transform::serialize() {
    nlohmann::json json;

    json["position"] = nlohmann::json::array({ position.x, position.y, position.z });
    json["rotation"] = nlohmann::json::array({ rotation.x, rotation.y, rotation.z });
    json["scale"] = nlohmann::json::array({ scale.x, scale.y, scale.z });

    return json;
}

void Transform::deserialize(const nlohmann::json& json) {
    position = Vector3(json["position"][0], json["position"][1], json["position"][2]);
    rotation = Vector3(json["rotation"][0], json["rotation"][1], json["rotation"][2]);
    scale = Vector3(json["scale"][0], json["scale"][1], json["scale"][2]);
}
