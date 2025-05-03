#include "Quack/Math/Math.hpp"
#include "Quack/Math/Matrix4.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/Transform.hpp"

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
