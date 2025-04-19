#ifndef QUACK_TEXTURE_HPP
#define QUACK_TEXTURE_HPP
#include <cstdint>

/**
 * @brief Representation of a 2D texture used in rendering.
 *
 * This class provides functionality to load, bind, and manage OpenGL textures.
 */
class Texture {
public:
    /**
     * @brief Default constructor.
     *
     * Does nothing, to initialize and load data, use create() method.
     */
    Texture();

    /**
     * @brief Load a texture from an image file.
     *
     * @param filename Path to the image file.
     * @return True if the texture was successfully loaded and created, false otherwise.
     */
    bool create(const char* filename);

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
private:
    /**
     * @brief Generate the OpenGL texture object.
     */
    void generate();

    /**
     * @brief Load image data from a file and upload it to the GPU.
     *
     * @param filename Path to the image file.
     * @return True if loading and uploading succeeded, false otherwise.
     */
    bool loadFromFile(const char* filename);

    uint32_t m_id;
};

#endif //QUACK_TEXTURE_HPP
