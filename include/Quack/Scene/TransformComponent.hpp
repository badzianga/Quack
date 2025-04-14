#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP
#include "Quack/Scene/Component.hpp"
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformComponent final : public Component {
public:
    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};
    glm::vec3 scale{1.f};

    void start() override {}

    void update() override {}

    [[nodiscard]] glm::vec3 getForward() const {
        glm::vec4 forward = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
        auto rotationMatrix = glm::mat4(1.0f);
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        forward = rotationMatrix * forward;
        return forward;
    }

    [[nodiscard]] glm::vec3 getRight() const {
        return glm::normalize(glm::cross(getForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    [[nodiscard]] glm::vec3 getUp() const {
        return glm::normalize(glm::cross(getRight(), getForward()));
    }
};

#endif //TRANSFORM_COMPONENT_HPP
