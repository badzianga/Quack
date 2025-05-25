#include "Quack/Scene/Scene.hpp"
#include "Quack/Utils/Logger.hpp"
#include <algorithm>
#include <nlohmann/json.hpp>

GameObject* Scene::createGameObject(const char* name) {
    // set unique name for game object (add a number) if name already exists
    // TODO: very inefficient code here, maybe this can be made better?
    std::string nameStr = name;
    const std::string originalName = name;

    int suffix = 1;
    bool nameExists;
    do {
        nameExists = false;
        for (const auto& gameObject: m_gameObjects) {
            if (gameObject->name == nameStr) {
                nameExists = true;
                break;
            }
        }
        if (nameExists) {
            nameStr = originalName + std::to_string(++suffix);
        }
    } while (nameExists);

    m_gameObjects.emplace_back(std::make_unique<GameObject>(nameStr.c_str()));
    Logger::debug() << "GameObject created on the scene";
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
    Logger::debug() << "GameObject removed from the scene";
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

std::vector<std::unique_ptr<GameObject>>& Scene::getAllGameObjects() {
    return m_gameObjects;
}

void Scene::clear() {
    name.clear();
    m_gameObjects.clear();
}

nlohmann::json Scene::serialize() {
    nlohmann::json json;

    json["name"] = name;
    json["gameObjects"] = nlohmann::json::array();
    for (auto& gameObject : m_gameObjects) {
        json["gameObjects"].push_back(gameObject->serialize());
    }

    return json;
}

void Scene::deserialize(const nlohmann::json& json) {
    name = json["name"].get<std::string>();
    for (auto& gameObjectJson : json["gameObjects"]) {
        GameObject* gameObject = createGameObject(gameObjectJson["name"].get<std::string>().c_str());
        gameObject->deserialize(gameObjectJson);
    }
}
