#ifndef QUACK_GAME_OBJECT_HPP
#define QUACK_GAME_OBJECT_HPP
#include "Quack/Scene/Component.hpp"
#include "Quack/Scene/TransformComponent.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>

class GameObject {
public:
    explicit GameObject(const char* name = "GameObject") : m_name(name) {
        addComponent<TransformComponent>();
    }

    template <typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

        auto typeIdx = std::type_index(typeid(T));
        if (m_components.contains(typeIdx)) {
            return static_cast<T*>(m_components[typeIdx].get());
        }

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->gameObject = this;
        T* rawPtr = component.get();
        m_components[typeIdx] = std::move(component);
        return rawPtr;
    }

    template <typename T>
    T* getComponent() {
        static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

        auto typeIdx = std::type_index(typeid(T));
        auto it = m_components.find(typeIdx);
        if (it != m_components.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    template <typename T>
    bool hasComponent() {
        return getComponent<T>() != nullptr;
    }

    template <typename T>
    void removeComponent() {
        static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

        auto typeIdx = std::type_index(typeid(T));
        m_components.erase(typeIdx);
    }

    void startAllComponents() {
        for (auto& pair : m_components) {
            if (pair.second->enabled) {
                pair.second->start();
            }
        }
    }

    void updateAllComponents() {
        if (!m_active) return;

        for (auto& pair : m_components) {
            if (pair.second->enabled) {
                pair.second->update();
            }
        }
    }

    [[nodiscard]] bool isActive() const {
        return m_active;
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
    std::string m_name;
    bool m_active = true;
};

#endif //QUACK_GAME_OBJECT_HPP
