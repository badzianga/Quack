#ifndef QUACK_ENGINE_HPP
#define QUACK_ENGINE_HPP

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
    bool destroy();

    virtual void onCreate() = 0;
    virtual void onUpdate() = 0;
    virtual void onDestroy() = 0;
};

#endif //QUACK_ENGINE_HPP
