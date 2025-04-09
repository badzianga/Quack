#ifndef QUACK_ENGINE_HPP
#define QUACK_ENGINE_HPP
#include "Quack/Core/Window.hpp"

class Engine {
public:
    Engine() = default;
    virtual ~Engine() = default;

    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

    bool create();
    void start();
    void stop();
    bool destroy();

    void setWindowClearColor(float red, float green, float blue, float alpha);

    virtual void onCreate() = 0;
    virtual void onUpdate() = 0;
    virtual void onDestroy() = 0;
private:
    Window m_window;
};

#endif //QUACK_ENGINE_HPP
