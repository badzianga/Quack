#include "Renderer.hpp"
#include <glad/glad.h>

void Renderer::clear(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}
