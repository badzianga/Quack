#ifndef QUACK_MESH_RENDERER_COMPONENT_HPP
#define QUACK_MESH_RENDERER_COMPONENT_HPP
#include "Quack/Graphics/Material.hpp"
#include "Quack/Graphics/Mesh.hpp"
#include "Quack/Graphics/Shader.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/Component.hpp"
#include "Quack/Scene/GameObject.hpp"
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MeshRendererComponent final : public Component {
public:
    Mesh mesh;
    Shader shader;
    Material material;

    void start() override {}

    void update() override {
        // TODO: update only if enabled
        auto transform = gameObject->getComponent<TransformComponent>();
        assert(transform != nullptr);

        glm::mat4 model = getModelMatrix(transform);
        glm::mat4 mvp = CameraComponent::getStaticProjectionView() * model;

        shader.use();
        shader.set("u_mvp", mvp);
        shader.set("u_colorMap", material.colorMap);
        mesh.draw();
    }
private:
    static glm::mat4 getModelMatrix(const TransformComponent* transform) {
        glm::mat4 model{1.f};

        model = glm::translate(model, transform->position);
        model = glm::rotate(model, glm::radians(transform->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(transform->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(transform->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, transform->scale);

        return model;
    }
};

#endif //QUACK_MESH_RENDERER_COMPONENT_HPP
