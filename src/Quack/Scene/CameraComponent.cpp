#include "Quack/Math/Math.hpp"
#include "Quack/Math/Matrix4.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/Transform.hpp"
#include <nlohmann/json.hpp>

Matrix4 CameraComponent::s_projectionView{1.f};

void CameraComponent::start() {}

void CameraComponent::update() {
    if (!enabled) return;

    s_projectionView = getProjectionViewMatrix();
}

Matrix4 CameraComponent::getViewMatrix() const {
    Vector3 position = gameObject->transform.position;
    Vector3 forward = gameObject->transform.getForward();
    Vector3 up = gameObject->transform.getUp();

    return Math::lookAt(position, position + forward, up);
}

Matrix4 CameraComponent::getProjectionMatrix() const {
    if (projectionType == ProjectionType::Perspective) {
        return Math::perspective(Math::toRadians(fieldOfView), aspectRatio, nearClip, farClip);
    }
    const float halfHeight = orthoSize * 0.5f;
    const float halfWidth = halfHeight * aspectRatio;
    return Math::orthographic(-halfWidth, halfWidth, -halfHeight, halfHeight, nearClip, farClip);
}

Matrix4 CameraComponent::getProjectionViewMatrix() const {
    return getProjectionMatrix() * getViewMatrix();
}

Matrix4 CameraComponent::getStaticProjectionView() {
    return s_projectionView;
}

nlohmann::json CameraComponent::serialize() {
    nlohmann::json json;

    json["componentType"] = "Camera";
    json["enabled"] = enabled;
    json["projectionType"] = projectionType;
    json["fieldOfView"] = fieldOfView;
    json["nearClip"] = nearClip;
    json["farClip"] = farClip;
    json["aspectRatio"] = aspectRatio;
    json["orthoSize"] = orthoSize;

    return json;
}

void CameraComponent::deserialize(const nlohmann::json& json) {
    enabled = json["enabled"];
    projectionType = static_cast<ProjectionType>(json["projectionType"]);
    fieldOfView = json["fieldOfView"];
    nearClip = json["nearClip"];
    farClip = json["farClip"];
    aspectRatio = json["aspectRatio"];
    orthoSize = json["orthoSize"];
}
