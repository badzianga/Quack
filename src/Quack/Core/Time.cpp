#include "Quack/Core/Time.hpp"
#include <GLFW/glfw3.h>

Time Time::s_instance;

Time::Time() : m_deltaTime(0.f), m_lastFrameTime(0.f) {}

float Time::getDeltaTime() {
    return s_instance.m_deltaTime;
}

int Time::getFPS() {
    return static_cast<int>(1.f / s_instance.m_deltaTime);
}

void Time::update() {
    auto currentFrameTime = static_cast<float>(glfwGetTime());

    s_instance.m_deltaTime = currentFrameTime - s_instance.m_lastFrameTime;
    s_instance.m_lastFrameTime = currentFrameTime;
}
