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
    void close();
    bool destroy();
    void setClearColor(float r, float g, float b, float a) const;
    void clear() const;
private:
    GLFWwindow* p_window;

    friend class Engine;

    static constexpr int DEFAULT_WIDTH = 1024;
    static constexpr int DEFAULT_HEIGHT = 768;
    static constexpr auto DEFAULT_TITLE = "Quack Window";
};

#endif //QUACK_WINDOW_HPP
