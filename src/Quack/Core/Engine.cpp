#include "Quack/Core/Engine.hpp"

bool Engine::create() {
    m_window.create(1024, 768, "Quack Engine");

    this->onCreate();

    return true;
}

void Engine::start() {
    while (m_window.isOpen()) {
        this->onUpdate();

        m_window.update();
    }
}

bool Engine::destroy() {
    m_window.destroy();

    this->onDestroy();

    return true;
}
