#ifndef QUACK_TRANSFORM_COMPONENT_HPP
#define QUACK_TRANSFORM_COMPONENT_HPP
#include "Quack/Scene/Component.hpp"
#include <glm/mat4x4.hpp>

class TransformComponent final : public Component {
public:
    void start() override;
    void update() override;

    [[nodiscard]] glm::vec3 getForward() const;
    [[nodiscard]] glm::vec3 getRight() const;
    [[nodiscard]] glm::vec3 getUp() const;

    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};
    glm::vec3 scale{1.f};
};

#endif //QUACK_TRANSFORM_COMPONENT_HPP
