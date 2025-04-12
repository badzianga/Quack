#ifndef QUACK_SCENE_HPP
#define QUACK_SCENE_HPP
#include "Quack/Scene/GameObject.hpp"
#include <algorithm>
#include <memory>
#include <vector>

class Scene {
public:
    GameObject* createGameObject(const char* name = "Entity") {
        m_gameObjects.emplace_back(std::make_unique<GameObject>(name));
        return m_gameObjects.back().get();
    }

    void removeGameObject(GameObject* gameObject) {
        auto it = std::remove_if(
            m_gameObjects.begin(),
            m_gameObjects.end(),
            [gameObject](const std::unique_ptr<GameObject>& obj) {
                return obj.get() == gameObject;
            });
        m_gameObjects.erase(it, m_gameObjects.end());
    }

    void startAllGameObjects() {
        for (auto& gameObject : m_gameObjects) {
            gameObject->startAllComponents();
        }
    }

    void updateAllGameObjects() {
        for (auto& gameObject : m_gameObjects) {
            gameObject->updateAllComponents();
        }
    }

    template <typename T>
    std::vector<T*> getAllComponents() {
        std::vector<T*> result;
        for (auto& gameObject : m_gameObjects) {
            if (gameObject->isActive()) {
                T* component = gameObject->getComponent<T>();
                if (component != nullptr) {
                    result.push_back(component);
                }
            }
        }
        return result;
    }
private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
};

#endif //QUACK_SCENE_HPP
