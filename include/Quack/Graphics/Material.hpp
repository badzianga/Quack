#ifndef QUACK_MATERIAL_HPP
#define QUACK_MATERIAL_HPP
#include "Quack/Graphics/Color.hpp"
#include "Quack/Utils/UUID.hpp"

/**
 * @brief Simple structure representing a material's visual properties.
 *
 * Currently, it only includes a base color (color map), and texture but will be extended
 * to include shininess, specular highlights, normals, etc.
 */
struct Material {
    /**
     * @brief RGBA base color of the material.
     *
     * Default value is white.
     * Texture is multiplied by this color.
     * If texture is not specified, then only this color
     * is used as a base color for the material.
     */
    Color baseColor = Color::White;

    /**
     * @brief UUID of the texture of the material.
     *
     * If it is not specified, then only color is used for the material.
     */
    UUID baseMap{ 0 };
};

#endif //QUACK_MATERIAL_HPP
