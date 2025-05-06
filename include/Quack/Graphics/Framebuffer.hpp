#ifndef QUACK_FRAMEBUFFER_HPP
#define QUACK_FRAMEBUFFER_HPP
#include "Quack/Graphics/Texture.hpp"
#include "Quack/Math/Vector2.hpp"

class Framebuffer {
public:
    Framebuffer();
    ~Framebuffer();
    Framebuffer(const Framebuffer&) = delete;
    Framebuffer(Framebuffer&&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;
    Framebuffer& operator=(Framebuffer&&) = delete;

    bool create(int width, int height);
    bool destroy();

    void bind() const;
    void unbind() const;

    [[nodiscard]] uint32_t getId() const;
    [[nodiscard]] uint32_t getTextureID() const;
    [[nodiscard]] Vector2 getSize() const;
private:
    uint32_t m_fbo;
    uint32_t m_rbo;
    Texture m_texture;
};

#endif //QUACK_FRAMEBUFFER_HPP
