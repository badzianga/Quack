#ifndef QUACK_GAME_OBJECT_HPP
#define QUACK_GAME_OBJECT_HPP
#include "Quack/Scene/Component.hpp"
#include "Quack/Scene/Transform.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

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
     * @param parent Pointer to the parent.
     */
    explicit GameObject(const char* name = "GameObject", GameObject* parent = nullptr);

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
     * @brief Call start() on all attached components and children components.
     *
     * This method is called by Scene::startAllGameObjects(),
     * so it should not be called by user.
     */
    void startAllComponents() const;

    /**
     * @brief Call update() on all attached components and children components.
     *
     * This method is called by Scene::updateAllGameObjects(),
     * so it should not be called by user.
     */
    void updateAllComponents() const;

    /**
     * @brief Create and add a new GameObject as a child.
     *
     * If GameObject already has a child with the same name as passed,
     * then suffix is calculated and added.
     *
     * @param name Optional name for the game object.
     * @return Pointer to the created GameObject.
     */
    GameObject* addChild(const char* name = "GameObject");

    /**
     * @brief Remove a GameObject from the children.
     *
     * @param child Pointer to the GameObject to remove.
     */
    void removeChild(GameObject* child);

    /**
     * @brief Get all children of this GameObject.
     *
     * @return Vector of pointers to the children of this GameObject.
     */
    std::vector<std::unique_ptr<GameObject>>& getChildren();

    /// Transform pseudo-component which contains transformation-related vectors.
    Transform transform{};

    /// Indicate whether the game object is active (updated every frame).
    bool active = true;

     /// Name assigned to the GameObject.
    std::string name;

    /// Pointer to the parent GameObject in the hierarchy (null if child of scene).
    GameObject* parent = nullptr;
private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
    std::vector<std::unique_ptr<GameObject>> m_children;
};

#endif //QUACK_GAME_OBJECT_HPP

#include "Quack/Scene/GameObject.inl"
