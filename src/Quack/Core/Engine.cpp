#include "Quack/Core/Engine.hpp"

bool Engine::create() {
    this->onCreate();

    return true;
}

void Engine::start() {
    while (true) {
        this->onUpdate();

        break;
    }
}

bool Engine::destroy() {
    this->onDestroy();

    return true;
}
