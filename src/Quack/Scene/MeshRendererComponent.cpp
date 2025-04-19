#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/MeshRendererComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

void MeshRendererComponent::start() {}

void MeshRendererComponent::update() {
    // TODO: update only if enabled
    const auto transform = gameObject->getComponent<TransformComponent>();
    assert(transform != nullptr);

    glm::mat4 model = getModelMatrix(transform);
    glm::mat4 mvp = CameraComponent::getStaticProjectionView() * model;

    shader.use();
    shader.set("u_mvp", mvp);
    shader.set("u_baseColor", material.baseColor);
    shader.set("u_hasBaseMap", material.baseMap != nullptr);
    mesh.draw();
}

glm::mat4 MeshRendererComponent::getModelMatrix(const TransformComponent* transform) {
    glm::mat4 model{1.f};

    model = glm::translate(model, transform->position);
    model = glm::rotate(model, glm::radians(transform->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(transform->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(transform->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, transform->scale);

    return model;
}
