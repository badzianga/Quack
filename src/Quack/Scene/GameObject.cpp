#include "Quack/Scene/GameObject.hpp"

GameObject::GameObject(const char* name) : m_name(name) {}

void GameObject::startAllComponents() const {
    for (auto& pair : m_components) {
        if (pair.second->enabled) {
            pair.second->start();
        }
    }
}

void GameObject::updateAllComponents() const {
    if (!active) return;

    for (auto& pair : m_components) {
        if (pair.second->enabled) {
            pair.second->update();
        }
    }
}

