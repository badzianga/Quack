#include "Quack/Core.hpp"
#include "Quack/Utils/Logger.hpp"

bool Engine::create(int width, int height, const char* title) {
    m_window.create(width, height, title);
    Input::init(m_window.p_window);

    this->onCreate();

    Logger::debug() << "Engine created";
    return true;
}

void Engine::start() {
    Logger::debug() << "Engine loop started";
    while (m_window.isOpen()) {
        Time::update();
        m_window.clear();

        this->onUpdate();

        m_window.update();
    }
    Logger::debug() << "Engine loop finished";
}

void Engine::stop() {
    m_window.close();
    Logger::debug() << "Engine stopped";
}

bool Engine::destroy() {
    this->onDestroy();

    m_window.destroy();
    Logger::debug() << "Engine destroyed";
    return true;
}

const Window& Engine::accessWindow() const {
    return m_window;
}
