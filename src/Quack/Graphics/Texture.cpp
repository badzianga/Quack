#include "Quack/Graphics/Texture.hpp"
#include "Quack/Utils/Logger.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/glew.h>
#include <oneapi/tbb/task_group.h>

Texture::Texture() : m_id(0) {}

bool Texture::create(const char* filename, WrapMode wrapMode, FilterMode filterMode) {
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    uint8_t* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data) {
        Logger::error("Texture " + std::string(filename) + " not found");
        return false;
    }

    int format;
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

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    initialize(wrapMode, filterMode);

    stbi_image_free(data);
    m_size = { static_cast<float>(width), static_cast<float>(height) };
    return true;
}

bool Texture::create(int width, int height) {
    m_size = { static_cast<float>(width), static_cast<float>(height) };
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    initialize(WrapMode::Repeat, FilterMode::Linear);

    return true;
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

void Texture::initialize(WrapMode wrap, FilterMode filter) const {
    (void) m_id;
    int wrapMode = GL_REPEAT;
    switch (wrap) {
        case WrapMode::Repeat: {
            wrapMode = GL_REPEAT;
        } break;
        case WrapMode::MirroredRepeat: {
            wrapMode = GL_MIRRORED_REPEAT;
        } break;
        case WrapMode::ClampToEdge: {
            wrapMode = GL_CLAMP_TO_EDGE;
        } break;
        case WrapMode::ClampToBorder: {
            wrapMode = GL_CLAMP_TO_BORDER;
        } break;
    }

    int filterMode = (filter == FilterMode::Nearest) ? GL_NEAREST : GL_LINEAR;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

    if (filter == FilterMode::Linear) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

uint32_t Texture::getId() const {
    return m_id;
}

Vector2 Texture::getSize() const {
    return m_size;
}
