#ifndef QUACK_TEXTURE_HPP
#define QUACK_TEXTURE_HPP
#include "Quack/Math/Vector2.hpp"
#include <cstdint>

/**
 * @brief Representation of a 2D texture used in rendering.
 *
 * This class provides functionality to load, bind, and manage OpenGL textures.
 */
class Texture {
public:
    /**
     * @brief Enumeration for texture wrapping modes.
     *
     * Defines how textures are sampled when texture coordinates are outside the standard [0, 1] range.
     */
    enum class WrapMode { Repeat, MirroredRepeat, ClampToEdge, ClampToBorder };

    /**
     * @brief Enumeration for texture filtering modes.
     *
     * Specifies the method used to sample a texture when it is rendered
     * at a size different from its original resolution.
     */
    enum class FilterMode { Nearest, Linear };

    /**
     * @brief Default constructor.
     *
     * Does nothing, to initialize and load data, use create() method.
     */
    Texture();

    /**
     * @brief Create and load a texture from a file.
     *
     * This method initializes a texture by loading the image data from the specified file
     * and applying the specified wrapping and filtering modes.
     *
     * @param filename Path to the texture image file.
     * @param wrapMode Texture wrapping mode to use (default is WrapMode::Repeat).
     * @param filterMode Texture filtering mode to use (default is FilterMode::Linear).
     * @return True if the texture was successfully created, false otherwise.
     */
    bool create(const char* filename, WrapMode wrapMode = WrapMode::Repeat, FilterMode filterMode = FilterMode::Linear);

    /**
     * @brief Create an empty texture with the specified dimensions.
     *
     * Allocates a 2D texture in GPU memory with the given width and height.
     *
     * @param width Width of the texture in pixels.
     * @param height Height of the texture in pixels.
     * @return True if the texture was successfully created, false otherwise.
     */
    bool create(int width, int height);

    /**
     * @brief Destroy the texture and free associated GPU resources.
     *
     * @return True if the texture was successfully destroyed, false if it was already invalid.
     */
    bool destroy();

    /**
     * @brief Bind the texture to a given texture unit.
     *
     * This method should not be used by the user, it is used automatically during rendering.
     *
     * @param unit Texture unit index to bind the texture to (default is 0).
     */
    void bind(uint32_t unit = 0) const;

    [[nodiscard]] uint32_t getId() const;
    [[nodiscard]] Vector2 getSize() const;

private:
    /**
     * @brief Initialize the OpenGL texture object.
     */
    void initialize(WrapMode wrap, FilterMode filter) const;

    uint32_t m_id;
    Vector2 m_size;
};

#endif //QUACK_TEXTURE_HPP
