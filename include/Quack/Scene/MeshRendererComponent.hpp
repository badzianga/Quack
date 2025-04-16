#ifndef QUACK_MESH_RENDERER_COMPONENT_HPP
#define QUACK_MESH_RENDERER_COMPONENT_HPP
#include "Quack/Graphics.hpp"
#include "Quack/Scene/Component.hpp"
#include "Quack/Scene/TransformComponent.hpp"

class MeshRendererComponent final : public Component {
public:
    void start() override;
    void update() override;

    Mesh mesh;
    Shader shader;
    Material material;
private:
    static glm::mat4 getModelMatrix(const TransformComponent* transform);
};

#endif //QUACK_MESH_RENDERER_COMPONENT_HPP
