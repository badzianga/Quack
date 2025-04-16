#ifndef QUACK_SCENE_HPP
#define QUACK_SCENE_HPP
#include "Quack/Scene/GameObject.hpp"
#include <memory>
#include <vector>

class Scene {
public:
    GameObject* createGameObject(const char* name = "GameObject");

    void removeGameObject(GameObject* gameObject);

    void startAllGameObjects() const;

    void updateAllGameObjects() const;

    // TODO: Currently unused
    // template <typename T>
    // std::vector<T*> getAllComponents() {
    //     std::vector<T*> result;
    //     for (auto& gameObject : m_gameObjects) {
    //         if (gameObject->isActive()) {
    //             T* component = gameObject->getComponent<T>();
    //             if (component != nullptr) {
    //                 result.push_back(component);
    //             }
    //         }
    //     }
    //     return result;
    // }
private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
};

#endif //QUACK_SCENE_HPP
