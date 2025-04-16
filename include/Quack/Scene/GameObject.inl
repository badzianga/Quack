#ifndef QUACK_GAME_OBJECT_INL
#define QUACK_GAME_OBJECT_INL
#include "Quack/Scene/GameObject.hpp"

template <typename T, typename... Args>
T* GameObject::addComponent(Args&&... args) {
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
T* GameObject::getComponent() {
    static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

    auto typeIdx = std::type_index(typeid(T));
    auto it = m_components.find(typeIdx);
    if (it != m_components.end()) {
        return static_cast<T*>(it->second.get());
    }
    return nullptr;
}

template <typename T>
bool GameObject::hasComponent() {
    return getComponent<T>() != nullptr;
}

template <typename T>
void GameObject::removeComponent() {
    static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

    auto typeIdx = std::type_index(typeid(T));
    m_components.erase(typeIdx);
}

#endif //QUACK_GAME_OBJECT_INL
