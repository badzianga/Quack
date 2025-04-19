#include "Quack/Graphics/Texture.hpp"
#include "Quack/Utils/Logger.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

Texture::Texture() : m_id(0) {}

bool Texture::create(const char* filename) {
    return loadFromFile(filename);
}

bool Texture::destroy() {
    glDeleteTextures(1, &m_id);
    m_id = 0;

    return true;
}

void Texture::bind(uint32_t unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::generate() {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

bool Texture::loadFromFile(const char* filename) {
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    uint8_t* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data) {
        Logger::error("Texture " + std::string(filename) + " not found");
        return false;
    }

    GLenum format;
    switch (nrChannels) {
        case 1: {
            format = GL_RED;
        } break;
        case 3: {
            format = GL_RGB;
        } break;
        case 4: {
            format = GL_RGBA;
        } break;
        default:
            Logger::error("Unsupported number of channels");
            return false;
    }

    generate();

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(format), width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return true;
}
