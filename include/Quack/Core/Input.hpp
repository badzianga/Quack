#ifndef QUACK_INPUT_HPP
#define QUACK_INPUT_HPP
#include "Quack/Core/Keyboard.hpp"
#include <unordered_map>

struct GLFWwindow;

class Input {
public:
    Input(const Input&) = delete;
    Input(Input&&) = delete;
    Input& operator=(const Input&) = delete;
    Input& operator=(Input&&) = delete;

    static bool isKeyPressed(Keyboard::Key key);
    static bool isKeyReleased(Keyboard::Key key);
    static bool isKeyDown(Keyboard::Key key);
private:
    Input();

    static void init(GLFWwindow* window);

    static Input s_instance;
    GLFWwindow* p_window;
    std::unordered_map<int, bool> m_keyPreviousState;

    friend class Engine;
};

#endif //QUACK_INPUT_HPP
