#ifndef QUACK_MATERIAL_HPP
#define QUACK_MATERIAL_HPP
#include "Quack/Graphics/Color.hpp"

/**
 * @brief Simple structure representing a material's visual properties
 *
 * Currently, it only includes a base color (color map), but will be extended
 * to include textures, shininess, specular highlights, etc.
 */
struct Material {
    /**
     * @brief RGBA base color of the material.
     *
     * Default value is white.
     */
    Color colorMap = Color::White;
};

#endif //QUACK_MATERIAL_HPP
