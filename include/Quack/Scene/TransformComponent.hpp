#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP
#include "Quack/Scene/Component.hpp"
#include <glm/vec3.hpp>

class TransformComponent final : public Component {
public:
    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};
    glm::vec3 scale{1.f};

    void start() override {}

    void update() override {}
};

#endif //TRANSFORM_COMPONENT_HPP
