#ifndef QUACK_GLOBAL_LIGHT_HPP
#define QUACK_GLOBAL_LIGHT_HPP
#include "Quack/Graphics/Color.hpp"
#include "Quack/Math/Vector3.hpp"

/**
 * @brief Configuration of global light.
 *
 * This class stores data of the global direction light.
 */
class GlobalLight {
public:
    /// Color of the light (Color::White by default).
    static Color color;

    /// Intensity of the ambient light (0.1f by default).
    static float ambientIntensity;

    /// Direction of the light ((1.f, -1.f, -0.5f) by default, will be normalized).
    static Vector3 direction;
};

#endif //QUACK_GLOBAL_LIGHT_HPP
