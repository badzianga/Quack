#include "Quack/Core/Input.hpp"
#include "Quack/Utils/Logger.hpp"
#include <GLFW/glfw3.h>

Input Input::s_instance;

Input::Input() : p_window(nullptr) {}

void Input::init(GLFWwindow* window) {
    s_instance.p_window = window;

    Logger::debug() << "Input initialized";
}

bool Input::isKeyPressed(Keyboard::Key key) {
    int keyCode = static_cast<int>(key);
    if (glfwGetKey(s_instance.p_window, keyCode) == GLFW_PRESS) {
        bool wasPressed = s_instance.m_keyPreviousState[keyCode];
        s_instance.m_keyPreviousState[keyCode] = true;
        return !wasPressed;
    }
    s_instance.m_keyPreviousState[keyCode] = false;
    return false;
}

bool Input::isKeyReleased(Keyboard::Key key) {
    int keyCode = static_cast<int>(key);
    return glfwGetKey(s_instance.p_window, keyCode) == GLFW_RELEASE && s_instance.m_keyPreviousState[keyCode];
}

bool Input::isKeyDown(Keyboard::Key key) {
    int keyCode = static_cast<int>(key);
    return glfwGetKey(s_instance.p_window, keyCode) == GLFW_PRESS;
}

bool Input::isButtonPressed(Mouse::Button button) {
    int mouseButton = static_cast<int>(button);
    return glfwGetMouseButton(s_instance.p_window, mouseButton) == GLFW_PRESS;
}

Vector2 Input::getMousePosition() {
    double x;
    double y;
    glfwGetCursorPos(s_instance.p_window, &x, &y);
    return { static_cast<float>(x), static_cast<float>(y) };
}
