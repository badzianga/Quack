#include "Quack/Graphics/Framebuffer.hpp"
#include "Quack/Utils/Logger.hpp"
#include <GL/glew.h>

Framebuffer::Framebuffer(): m_fbo(0), m_rbo(0) {}

Framebuffer::~Framebuffer() = default;

bool Framebuffer::create(int width, int height) {
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    m_texture.create(width, height);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        m_texture.getId(),
        0
    );

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH24_STENCIL8,
        width,
        height
    );
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER,
        m_rbo
    );

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        Logger::error("Framebuffer is incomplete");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

bool Framebuffer::destroy() {
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteRenderbuffers(1, &m_rbo);
    m_texture.destroy();
    return true;
}

void Framebuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(
        0, 0,
        static_cast<int>(m_texture.getSize().x),
        static_cast<int>(m_texture.getSize().y)
    );
}

void Framebuffer::unbind() const {
    (void) m_fbo;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t Framebuffer::getId() const {
    return m_fbo;
}

uint32_t Framebuffer::getTextureID() const {
    return m_texture.getId();
}

Vector2 Framebuffer::getSize() const {
    return m_texture.getSize();
}
