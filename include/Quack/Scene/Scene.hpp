#ifndef QUACK_SCENE_HPP
#define QUACK_SCENE_HPP
#include "Quack/Scene/GameObject.hpp"
#include <memory>
#include <vector>

/**
 * @brief %Scene representation with a collection of game objects.
 *
 * Manages the lifecycle of all game objects.
 * Handles creation, removal, initialization, and per-frame updates.
 */
class Scene {
public:
    /**
     * @brief Create and add a new GameObject to the scene.
     *
     * @param name Optional name for the game object.
     * @return Pointer to the created GameObject.
     */
    GameObject* createGameObject(const char* name = "GameObject");

    /**
     * @brief Remove a GameObject from the scene.
     *
     * @param gameObject Pointer to the GameObject to remove.
     */
    void removeGameObject(GameObject* gameObject);

    /**
     * @brief Call start() on all GameObjects.
     *
     * Use once when the scene starts.
     */
    void startAllGameObjects() const;

    /**
     * @brief Call update() on all GameObjects.
     *
     * Call once per frame to update game logic.
     */
    void updateAllGameObjects() const;
private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
};

#endif //QUACK_SCENE_HPP
