#ifndef QUACK_TIME_HPP
#define QUACK_TIME_HPP

class Time {
public:
    Time(const Time&) = delete;
    Time(Time&&) = delete;
    Time& operator=(const Time&) = delete;
    Time& operator=(Time&&) = delete;

    static float getDeltaTime();
    static int getFPS();

private:
    Time();

    static void update();

    static Time s_instance;

    float m_deltaTime;
    float m_lastFrameTime;

    friend class Engine;
};

#endif //QUACK_TIME_HPP
