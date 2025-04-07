#include "Quack/Core/Input.hpp"
#include <GLFW/glfw3.h>

Input Input::s_instance;

Input::Input() : p_window(nullptr) {}

void Input::init(GLFWwindow* window) {
    s_instance.p_window = window;
}

bool Input::isKeyPressed(Key key) {
    int keyCode = static_cast<int>(key);
    if (glfwGetKey(s_instance.p_window, keyCode) == GLFW_PRESS) {
        bool wasPressed = s_instance.m_keyPreviousState[keyCode];
        s_instance.m_keyPreviousState[keyCode] = true;
        return !wasPressed;
    }
    s_instance.m_keyPreviousState[keyCode] = false;
    return false;
}

bool Input::isKeyReleased(Key key) {
    int keyCode = static_cast<int>(key);
    return glfwGetKey(s_instance.p_window, keyCode) == GLFW_RELEASE && s_instance.m_keyPreviousState[keyCode];
}

bool Input::isKeyDown(Key key) {
    int keyCode = static_cast<int>(key);
    return glfwGetKey(s_instance.p_window, keyCode) == GLFW_PRESS;
}
