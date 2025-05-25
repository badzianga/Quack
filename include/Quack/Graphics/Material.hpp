#ifndef QUACK_MATERIAL_HPP
#define QUACK_MATERIAL_HPP
#include "Quack/Graphics/Color.hpp"
#include "Quack/Graphics/Texture.hpp"

/**
 * @brief Simple structure representing a material's visual properties.
 *
 * Currently, it only includes a base color (color map), but will be extended
 * to include textures, shininess, specular highlights, etc.
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

    // TODO: this might be UUID of the texture?
    /**
     * @brief Texture of the material.
     *
     * If it is not specified, then only color is used for the material.
     *
     * Valid texture should be created somewhere else and address of it
     * should be set to this pointer to properly access it during rendering.
     */
    Texture* baseMap = nullptr;
};

#endif //QUACK_MATERIAL_HPP
