#ifndef QUACK_GLOBAL_LIGHT_HPP
#define QUACK_GLOBAL_LIGHT_HPP
#include "Color.hpp"

class GlobalLight {
public:
    static Color color;
    static float ambientIntensity;
};

#endif //QUACK_GLOBAL_LIGHT_HPP
