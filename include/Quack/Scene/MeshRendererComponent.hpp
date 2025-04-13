#ifndef QUACK_MESH_RENDERER_COMPONENT_HPP
#define QUACK_MESH_RENDERER_COMPONENT_HPP
#include "Quack/Graphics/Mesh.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/Component.hpp"
#include "Quack/Scene/GameObject.hpp"
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

class MeshRendererComponent final : public Component {
public:
    Mesh mesh;
    Shader shader;

    void start() override {}

    void update() override {
        // TODO: update only if enabled
        auto transform = gameObject->getComponent<TransformComponent>();
        assert(transform != nullptr);

        glm::mat4 model = getModelMatrix(transform);
        glm::mat4 mvp = CameraComponent::getStaticProjectionView() * model;

        shader.use();
        shader.set("u_mvp", mvp);
        mesh.draw();
    }
private:
    static glm::mat4 getModelMatrix(const TransformComponent* transform) {
        glm::mat4 model{1.f};

        model = glm::translate(model, transform->position);
        // TODO: rotate
        model = glm::scale(model, transform->scale);

        return model;
    }
};

#endif //QUACK_MESH_RENDERER_COMPONENT_HPP
