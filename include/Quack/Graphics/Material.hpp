#ifndef QUACK_MATERIAL_HPP
#define QUACK_MATERIAL_HPP
#include <glm/vec4.hpp>

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
     * Default value is white (1.0, 1.0, 1.0, 1.0).
     */
    glm::vec4 colorMap{1.f};
};

#endif //QUACK_MATERIAL_HPP
