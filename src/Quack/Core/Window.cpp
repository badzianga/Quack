#include "Quack/Core/Window.hpp"
#include "Quack/Utils/Logger.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>

Window::Window() : p_window(nullptr) {}

bool Window::create(int width, int height, const char* title) {
    if (width <= 0 || height <= 0) {
        width = DEFAULT_WIDTH;
        height = DEFAULT_HEIGHT;
        Logger::warn("Invalid width/height of the window. Setting to default 1024x768...");
    }
    if (title == nullptr || std::strlen(title) == 0) {
        title = DEFAULT_TITLE;
        Logger::warn("Invalid window title. Setting to default...");
    }

    if (!glfwInit()) {
        Logger::error("Failed to initialize GLFW3");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    p_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!p_window) {
        Logger::error("Failed to create GLFW window");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(p_window);
    if (glewInit() != GLEW_OK) {
        Logger::error("Failed to initialize GLEW");
        glfwDestroyWindow(p_window);
        glfwTerminate();
        return false;
    }

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    Logger::info(std::string("OpenGL API ") + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
    Logger::info(
        std::string("Using Device: ")
        + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR)))
        + " - "
        + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)))
    );
    Logger::debug("Window created");

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
    Logger::debug("Window closed");
}

bool Window::destroy() {
    glfwDestroyWindow(p_window);
    p_window = nullptr;

    Logger::debug("Window destroyed");
    return true;
}

void Window::setClearColor(Color color) const {
    (void) p_window;
    glClearColor(color.r, color.g, color.b, color.a);
}

void Window::clear() const {
    (void) p_window;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setCursorEnabled(bool enabled) const {
    if (enabled) {
        glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else {
        glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void Window::setVSyncEnabled(bool enabled) const {
    (void) p_window;
    glfwSwapInterval(enabled);
}
