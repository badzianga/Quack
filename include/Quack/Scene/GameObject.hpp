#ifndef QUACK_GAME_OBJECT_HPP
#define QUACK_GAME_OBJECT_HPP
#include "Quack/Scene/Component.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>

class GameObject {
public:
    explicit GameObject(const char* name = "GameObject");

    template <typename T, typename... Args>
    T* addComponent(Args&&... args);

    template <typename T>
    T* getComponent();

    template <typename T>
    bool hasComponent();

    template <typename T>
    void removeComponent();

    void startAllComponents() const;

    void updateAllComponents() const;

    [[nodiscard]] bool isActive() const;

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
    std::string m_name;
    bool m_active = true;
};

#endif //QUACK_GAME_OBJECT_HPP

#include "Quack/Scene/GameObject.inl"
