#include "Quack/Core/Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

Window::Window() : p_window(nullptr) {}

bool Window::create(int width, int height, const char* title) {
    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    p_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!p_window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(p_window);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(p_window);
        glfwTerminate();
        return false;
    }

    glViewport(0, 0, width, height);

    std::printf("OpenGL API %s\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    std::printf(
        "Using Device: %s - %s\n",
        reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
        reinterpret_cast<const char*>(glGetString(GL_RENDERER))
    );

    return true;
}

bool Window::isOpen() const {
    return !glfwWindowShouldClose(p_window);
}

void Window::update() const {
    glfwSwapBuffers(p_window);
    glfwPollEvents();
}

void Window::close() {
    glfwSetWindowShouldClose(p_window, true);
}

bool Window::destroy() {
    glfwDestroyWindow(p_window);
    p_window = nullptr;

    return true;
}
