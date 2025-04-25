#ifndef QUACK_GAME_OBJECT_HPP
#define QUACK_GAME_OBJECT_HPP
#include "Quack/Scene/Component.hpp"
#include "Quack/Scene/Transform.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>

/**
 * @brief Entity representation in the scene.
 *
 * A GameObject is a container for components that define its behavior.
 * Supports runtime composition using templated methods.
 */
class GameObject {
public:
    /**
     * @brief Construct a new GameObject with an optional name.
     *
     * @param name The name of the GameObject.
     */
    explicit GameObject(const char* name = "GameObject");

    /**
     * @brief Add a component of type T to this GameObject.
     *
     * @tparam T Component type.
     * @tparam Args Argument types for the component constructor/
     * @param args Arguments to forward to the component constructor.
     * @return Pointer to the newly added component.
     */
    template <typename T, typename... Args>
    T* addComponent(Args&&... args);

    /**
     * @brief Retrieve a component of type T.
     *
     * @tparam T Component type.
     * @return Pointer to the component, or nullptr if not found.
     */
    template <typename T>
    T* getComponent();

    /**
     * @brief Check whether this GameObject has a component of type T.
     *
     * @tparam T Component type.
     * @return True if the component exists, false otherwise.
     */
    template <typename T>
    bool hasComponent();

    /**
     * @brief Remove the component of type T from this GameObject.
     *
     * If GameObject doesn't have component, method does nothing.
     *
     * @tparam T Component type.
     */
    template <typename T>
    void removeComponent();

    /**
     * @brief Call start() on all attached components.
     *
     * This method is called by Scene::startAllGameObjects(),
     * so it should not be called by user.
     */
    void startAllComponents() const;

    /**
     * @brief Call update() on all attached components.
     *
     * This method is called by Scene::updateAllGameObjects(),
     * so it should not be called by user.
     */
    void updateAllComponents() const;

    /**
     * @brief Check whether the GameObject is active.
     *
     * @return True if active, false otherwise.
     */
    [[nodiscard]] bool isActive() const;

    // Transform pseudo-component which contains transformation-related vectors
    Transform transform{};

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
    std::string m_name;
    bool m_active = true;
};

#endif //QUACK_GAME_OBJECT_HPP

#include "Quack/Scene/GameObject.inl"
