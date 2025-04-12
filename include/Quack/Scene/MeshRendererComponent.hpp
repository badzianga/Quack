#ifndef QUACK_MESH_RENDERER_COMPONENT_HPP
#define QUACK_MESH_RENDERER_COMPONENT_HPP
#include "Quack/Graphics/Mesh.hpp"
#include "Quack/Scene/Component.hpp"

class MeshRendererComponent final : public Component {
public:
    Mesh mesh;
    Shader shader;

    void start() override {}

    void update() override {
        if (enabled) {
            mesh.draw(shader);
        }
    }
};

#endif //QUACK_MESH_RENDERER_COMPONENT_HPP
