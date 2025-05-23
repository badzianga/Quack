#ifndef QUACK_SCENE_HPP
#define QUACK_SCENE_HPP
#include "Quack/Scene/IJsonSerializable.hpp"
#include "Quack/Scene/GameObject.hpp"
#include <memory>
#include <vector>

/**
 * @brief %Scene representation with a collection of game objects.
 *
 * Manages the lifecycle of all game objects.
 * Handles creation, removal, initialization, and per-frame updates.
 */
class Scene : public IJsonSerializable {
public:
    /**
     * @brief Create and add a new GameObject to the scene.
     *
     * If scene already has a GameObject with the same name as passed,
     * then suffix is calculated and added.
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

    /**
     * @brief Get all GameObject from this scene.
     *
     * @return Vector of pointers to the GameObjects on the scene.
     */
    std::vector<std::unique_ptr<GameObject>>& getAllGameObjects();

    // TODO: temporary solution for scene switching
    void clear();

    nlohmann::json serialize() override;

    void deserialize(const nlohmann::json& json) override;

    /// Displayed name of the scene.
    std::string name = "SampleScene";
private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
};

#endif //QUACK_SCENE_HPP
