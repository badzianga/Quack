#ifndef QUACK_WINDOW_HPP
#define QUACK_WINDOW_HPP

struct GLFWwindow;

/**
 * @brief Wrapper class for a GLFW window.
 *
 * This class manages the lifecycle and basic operations
 * for the window using the GLFW library.
 */
class Window {
public:
    /**
     * @brief Deleted copy constructor.
     */
    Window(const Window&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    Window(Window&&) = delete;

    /**
     * @brief Deleted copy assignment.
     */
    Window& operator=(const Window&) = delete;

    /**
     * @brief Deleted move assignment.
     */
    Window& operator=(Window&&) = delete;

    /**
     * @brief Set visibility of the mouse cursor in the window.
     *
     * When disabled, the cursor is hidden and locked for applications.
     *
     * @param enabled True to show the cursor, false to hide it.
     */
    void setCursorEnabled(bool enabled) const;

    /**
     * @brief Set the clear color used before drawing each frame.
     *
     * @param r Red channel (0.f to 1.f).
     * @param g Green channel (0.f to 1.f).
     * @param b Blue channel (0.f to 1.f).
     * @param a Alpha channel (0.f to 1.f).
     */
    void setClearColor(float r, float g, float b, float a) const;
private:
    /**
     * @brief Default private constructor.
     *
     * This constructor doesn't actually create the window,
     * it is used only to declare the object in the Engine class.
     */
    Window();

    /**
     * @brief Create the window with given parameters.
     *
     * The window is created by the friend Engine class.
     *
     * @param width Width of the window in pixels.
     * @param height Height of the window in pixels.
     * @param title Title to be displayed in the window title bar.
     * @return True if the window was successfully created, false otherwise.
     */
    bool create(int width, int height, const char* title);

    /**
     * @brief Check if the window is still open.
     *
     * @return True if the window is opened, false if it is closed.
     */
    [[nodiscard]] bool isOpen() const;

    /**
     * @brief Process window events and swaps buffers.
     *
     * Should be called once per frame to keep the window responsive.
     */
    void update() const;

    /**
     * @brief Signal the window to close.
     */
    void close();

    /**
     * @brief Destroy the window and clean up resources.
     *
     * @return True if the window was successfully destroyed, false otherwise.
     */
    bool destroy();

    /**
     * @brief Clear the window using the current clear color.
     */
    void clear() const;

    GLFWwindow* p_window;

    static constexpr int DEFAULT_WIDTH = 1024;
    static constexpr int DEFAULT_HEIGHT = 768;
    static constexpr auto DEFAULT_TITLE = "Quack Window";

    friend class Engine;
};

#endif //QUACK_WINDOW_HPP
