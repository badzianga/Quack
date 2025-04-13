#ifndef QUACK_CAMERA_COMPONENT_HPP
#define QUACK_CAMERA_COMPONENT_HPP
#include "Quack/Scene/Component.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/TransformComponent.hpp"
#include <glm/matrix.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraComponent : public Component {
public:
    float fieldOfView = 60.f;
    float nearClip = 0.3f;
    float farClip = 1000.f;
    float aspectRatio = 4.f / 3.f;

    [[nodiscard]] glm::mat4 getViewMatrix() const {
        auto transform = gameObject->getComponent<TransformComponent>();
        assert(transform != nullptr);
        const glm::vec3& position = transform->position;
        glm::vec3 forward = getForward(transform);
        glm::vec3 up = getUp(transform);

        return glm::lookAt(position, position + forward, up);
    }

    [[nodiscard]] glm::mat4 getProjectionMatrix() const {
        return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClip, farClip);
    }

    [[nodiscard]] glm::mat4 getProjectionViewMatrix() const {
        return getProjectionMatrix() * getViewMatrix();
    }

    static glm::mat4 getStaticProjectionView() {
        return s_projectionView;
    }

    void start() override {}

    void update() override {
        s_projectionView = getProjectionViewMatrix();
    }
private:
    static glm::vec3 getForward(const TransformComponent* transform) {
        glm::vec4 forward = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
        const glm::vec3& rotation = transform->rotation;
        auto rotationMatrix = glm::mat4(1.0f);
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        forward = rotationMatrix * forward;
        return forward;
    }

    static glm::vec3 getRight(const TransformComponent* transform) {
        return glm::normalize(glm::cross(getForward(transform), glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    static glm::vec3 getUp(const TransformComponent* transform) {
        return glm::normalize(glm::cross(getRight(transform), getForward(transform)));
    }

    static glm::mat4 s_projectionView;
};

glm::mat4 CameraComponent::s_projectionView{1.f};

#endif //QUACK_CAMERA_COMPONENT_HPP
