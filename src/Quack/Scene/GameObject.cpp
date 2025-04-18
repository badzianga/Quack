#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/TransformComponent.hpp"

GameObject::GameObject(const char* name) : m_name(name) {
    addComponent<TransformComponent>();
}

void GameObject::startAllComponents() const {
    for (auto& pair : m_components) {
        if (pair.second->enabled) {
            pair.second->start();
        }
    }
}

void GameObject::updateAllComponents() const {
    if (!m_active) return;

    for (auto& pair : m_components) {
        if (pair.second->enabled) {
            pair.second->update();
        }
    }
}

bool GameObject::isActive() const {
    return m_active;
}
