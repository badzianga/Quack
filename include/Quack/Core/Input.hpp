#ifndef QUACK_INPUT_HPP
#define QUACK_INPUT_HPP
#include "Quack/Core/Key.hpp"
#include <unordered_map>

struct GLFWwindow;

class Input {
public:
    Input(const Input&) = delete;
    Input(Input&&) = delete;
    Input& operator=(const Input&) = delete;
    Input& operator=(Input&&) = delete;

    static bool isKeyPressed(Key key);
    static bool isKeyReleased(Key key);
    static bool isKeyDown(Key key);
private:
    Input();

    static void init(GLFWwindow* window);

    static Input s_instance;
    GLFWwindow* p_window;
    std::unordered_map<int, bool> m_keyPreviousState;

    friend class Engine;
};

#endif //QUACK_INPUT_HPP
