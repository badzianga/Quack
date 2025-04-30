#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/MeshRendererComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Quack/Graphics/GlobalLight.hpp"

void MeshRendererComponent::start() {}

void MeshRendererComponent::update() {
    if (!enabled) return;

    glm::mat4 model = getModelMatrix(gameObject->transform);
    glm::mat4 mvp = CameraComponent::getStaticProjectionView() * model;

    shader.use();
    shader.set("u_mvp", mvp);
    shader.set("u_baseColor", material.baseColor);
    if (material.baseMap != nullptr) {
        shader.set("u_hasBaseMap", true);
        material.baseMap->bind();
    }
    else {
        shader.set("u_hasBaseMap", false);
    }

    // Set lights even if the current shader doesn't support it
    shader.set("u_lightColor", GlobalLight::color);
    shader.set("u_ambientIntensity", GlobalLight::ambientIntensity);
    shader.set("u_lightDirection", GlobalLight::direction);
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
    shader.set("u_normalMatrix", normalMatrix);

    mesh.draw();

    // TODO: consider unbinding texture
}

glm::mat4 MeshRendererComponent::getModelMatrix(const Transform& transform) {
    glm::mat4 model{1.f};

    model = glm::translate(model, transform.position);
    model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, transform.scale);

    return model;
}
