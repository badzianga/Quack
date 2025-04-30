#ifndef QUACK_GLOBAL_LIGHT_HPP
#define QUACK_GLOBAL_LIGHT_HPP
#include "Color.hpp"
#include <glm/vec3.hpp>

class GlobalLight {
public:
    static Color color;
    static float ambientIntensity;
    static glm::vec3 direction;
};

#endif //QUACK_GLOBAL_LIGHT_HPP
