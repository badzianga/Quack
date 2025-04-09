#include "Quack/Core/Engine.hpp"
#include "Quack/Core/Input.hpp"
#include "Quack/Core/Time.hpp"

bool Engine::create() {
    m_window.create(1024, 768, "Quack Engine");
    Input::init(m_window.p_window);

    this->onCreate();

    return true;
}

void Engine::start() {
    while (m_window.isOpen()) {
        Time::update();
        m_window.clear();

        this->onUpdate();

        m_window.update();
    }
}

void Engine::stop() {
    m_window.close();
}

bool Engine::destroy() {
    m_window.destroy();

    this->onDestroy();

    return true;
}

void Engine::setWindowClearColor(float red, float green, float blue, float alpha) {
    m_window.setClearColor(red, green, blue, alpha);
}
