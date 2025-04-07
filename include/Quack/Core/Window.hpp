#ifndef QUACK_WINDOW_HPP
#define QUACK_WINDOW_HPP

struct GLFWwindow{};

class Window {
public:
    Window();
    ~Window() = default;

    Window(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;

    bool create(int width, int height, const char* title);
    [[nodiscard]] bool isOpen() const;
    void update() const;
    bool destroy();
private:
    GLFWwindow* p_window;
};

#endif //QUACK_WINDOW_HPP
