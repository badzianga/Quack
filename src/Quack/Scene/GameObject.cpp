#include "Quack/Scene/GameObject.hpp"
#include <algorithm>

GameObject::GameObject(const char* name, GameObject* parent) : name(name), parent(parent) {}

void GameObject::startAllComponents() const {
    for (auto& pair : m_components) {
        if (pair.second->enabled) {
            pair.second->start();
        }
    }

    for (auto& child : m_children) {
        child->startAllComponents();
    }
}

void GameObject::updateAllComponents() const {
    if (!active) return;

    for (auto& pair : m_components) {
        if (pair.second->enabled) {
            pair.second->update();
        }
    }

    for (auto& child : m_children) {
        child->updateAllComponents();
    }
}

GameObject* GameObject::addChild(const char* name) {
    std::string nameStr = name;
    const std::string originalName = name;

    int suffix = 1;
    bool nameExists;
    do {
        nameExists = false;
        for (const auto& child: m_children) {
            if (child->name == nameStr) {
                nameExists = true;
                break;
            }
        }
        if (nameExists) {
            nameStr = originalName + std::to_string(++suffix);
        }
    } while (nameExists);

    m_children.emplace_back(std::make_unique<GameObject>(nameStr.c_str(), this));

    return m_children.back().get();
}

void GameObject::removeChild(GameObject* child) {
    auto it = std::remove_if(
            m_children.begin(),
            m_children.end(),
            [child](const std::unique_ptr<GameObject>& obj) {
                return obj.get() == child;
            });
    m_children.erase(it, m_children.end());
}

std::vector<std::unique_ptr<GameObject>>& GameObject::getChildren() {
    return m_children;
}
