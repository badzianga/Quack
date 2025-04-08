#include "Quack/Graphics/Renderer.hpp"
#include "Quack/Graphics/Shader.hpp"
#include <glad/glad.h>


void Renderer::clear(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawTestTriangle() {
    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    Shader shader;
    shader.create("resources/shaders/position.vert", "resources/shaders/position.frag");
    shader.use();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    shader.destroy();
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}
