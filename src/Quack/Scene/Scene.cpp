#include "Quack/Scene/Scene.hpp"
#include <algorithm>

GameObject* Scene::createGameObject(const char* name) {
    m_gameObjects.emplace_back(std::make_unique<GameObject>(name));
    return m_gameObjects.back().get();
}

void Scene::removeGameObject(GameObject* gameObject) {
    auto it = std::remove_if(
        m_gameObjects.begin(),
        m_gameObjects.end(),
        [gameObject](const std::unique_ptr<GameObject>& obj) {
            return obj.get() == gameObject;
        });
    m_gameObjects.erase(it, m_gameObjects.end());
}

void Scene::startAllGameObjects() const {
    for (auto& gameObject : m_gameObjects) {
        gameObject->startAllComponents();
    }
}

void Scene::updateAllGameObjects() const {
    for (auto& gameObject : m_gameObjects) {
        gameObject->updateAllComponents();
    }
}
