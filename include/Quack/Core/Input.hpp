#ifndef QUACK_INPUT_HPP
#define QUACK_INPUT_HPP
#include "Quack/Core/Keyboard.hpp"
#include "Quack/Core/Mouse.hpp"
#include <unordered_map>
#include <glm/vec2.hpp>

struct GLFWwindow;

/**
 * @brief Handle input state for keyboard and mouse.
 *
 * Provides static utility methods to check key states
 * and retrieve mouse position. Internally stores previous
 * key states to allow edge detection (pressed/released).
 */
class Input {
public:
    /**
     * @brief Deleted copy constructor.
     */
    Input(const Input&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    Input(Input&&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    Input& operator=(const Input&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    Input& operator=(Input&&) = delete;

    /**
     * @brief Check if a key was just pressed.
     *
     * @param key Key to check.
     * @return True if the key was not pressed in the previous frame,
     *         but is pressed in the current one.
     */
    static bool isKeyPressed(Keyboard::Key key);

    /**
     * @brief Check if a key was just released.
     *
     * @param key Key to check.
     * @return True if the key was pressed in the previous frame,
     *         but is released in the current one.
     */
    static bool isKeyReleased(Keyboard::Key key);

    /**
     * @brief Check if a key is currently being held down.
     *
     * @param key Key to check.
     * @return True if the key is currently pressed.
     */
    static bool isKeyDown(Keyboard::Key key);

    /**
     * @brief Check if a button is currently pressed (down).
     *
     * @param button Button to check.
     * @return True if button is currently pressed.
     */
    static bool isButtonPressed(Mouse::Button button);

    /**
     * @brief Get the current position of the mouse cursor.
     *
     * @return Mouse coordinates in window space.
     */
    static glm::vec2 getMousePosition();
private:
    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    Input();

    /**
     * @brief Initialize the input system with a GLFW window.
     *
     * This method must be called before any input functions are used.
     * It is called by Engine class.
     *
     * @param window Pointer to the GLFW window used for input capture.
     */
    static void init(GLFWwindow* window);

    static Input s_instance;
    GLFWwindow* p_window;
    std::unordered_map<int, bool> m_keyPreviousState;

    friend class Engine;
};

#endif //QUACK_INPUT_HPP
