#include "Quack/Core.hpp"
#include "Quack/Utils/Logger.hpp"

bool Engine::create(int width, int height, const char* title) {
    m_window.create(width, height, title);
    Input::init(m_window.p_window);

    this->onCreate();

    Logger::debug("Engine created");
    return true;
}

void Engine::start() {
    Logger::debug("Engine loop started");
    while (m_window.isOpen()) {
        Time::update();
        m_window.clear();

        this->onUpdate();

        m_window.update();
    }
    Logger::debug("Engine loop finished");
}

void Engine::stop() {
    m_window.close();
    Logger::debug("Engine stopped");
}

bool Engine::destroy() {
    m_window.destroy();

    this->onDestroy();

    Logger::debug("Engine destroyed");
    return true;
}

void Engine::setWindowClearColor(float red, float green, float blue, float alpha) const {
    m_window.setClearColor(red, green, blue, alpha);
    Logger::debug("Window clear color changed");
}

void Engine::setWindowCursorEnabled(bool enabled) const {
    m_window.setCursorEnabled(enabled);
}
