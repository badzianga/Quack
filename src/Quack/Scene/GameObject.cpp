#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/MeshRendererComponent.hpp"
#include "Quack/Scene/ScriptComponent.hpp"
#include "Quack/Utils/Logger.hpp"
#include <algorithm>
#include <nlohmann/json.hpp>

GameObject::GameObject(const char* name, GameObject* parent) : name(name), parent(parent) {}

void GameObject::startAllComponents() const {
    for (auto& pair : m_components) {
        if (pair.second->enabled) {
            pair.second->start();
        }
    }

    for (auto& child : m_children) {
        child->startAllComponents();
    }
}

void GameObject::updateAllComponents() const {
    if (!active) return;

    for (auto& pair : m_components) {
        if (pair.second->enabled) {
            pair.second->update();
        }
    }

    for (auto& child : m_children) {
        child->updateAllComponents();
    }
}

GameObject* GameObject::addChild(const char* name) {
    std::string nameStr = name;
    const std::string originalName = name;

    int suffix = 1;
    bool nameExists;
    do {
        nameExists = false;
        for (const auto& child: m_children) {
            if (child->name == nameStr) {
                nameExists = true;
                break;
            }
        }
        if (nameExists) {
            nameStr = originalName + std::to_string(++suffix);
        }
    } while (nameExists);

    m_children.emplace_back(std::make_unique<GameObject>(nameStr.c_str(), this));

    Logger::debug() << "Child added to GameObject";

    return m_children.back().get();
}

void GameObject::removeChild(GameObject* child) {
    auto it = std::remove_if(
            m_children.begin(),
            m_children.end(),
            [child](const std::unique_ptr<GameObject>& obj) {
                return obj.get() == child;
            });
    m_children.erase(it, m_children.end());

    Logger::debug() << "Child removed from GameObject";
}

std::vector<std::unique_ptr<GameObject>>& GameObject::getChildren() {
    return m_children;
}

// UUID GameObject::getUUID() const {
//     return m_uuid;
// }

nlohmann::json GameObject::serialize() {
    nlohmann::json json;

    // json["uuid"] = static_cast<uint64_t>(getUUID());
    json["transform"] = transform.serialize();
    json["active"] = active;
    json["name"] = name;
    json["components"] = nlohmann::json::array();
    for (auto& component : m_components) {
        json["components"].push_back(component.second->serialize());
    }
    json["children"] = nlohmann::json::array();
    for (auto& child : m_children) {
        json["children"].push_back(child->serialize());
    }

    return json;
}

void GameObject::deserialize(const nlohmann::json& json) {
    // Creating a new GameObject generates UUID for it which will be immediately overwritten, but it's the cleanest solution
    // m_uuid = UUID(json["uuid"].get<uint64_t>());
    transform.deserialize(json["transform"]);
    active = json["active"];
    // name = json["name"].get<std::string>();  // name is set during object creation
    for (auto& componentJson : json["components"]) {
        std::string componentType = componentJson["componentType"].get<std::string>();
        Component* component = nullptr;
        if (componentType == "MeshRenderer") component = addComponent<MeshRendererComponent>();
        else if (componentType == "Camera") component = addComponent<CameraComponent>();
        else if (componentType == "Script") component = addComponent<ScriptComponent>();
        else Logger::error() << "Unknown component type passed during deserialization: " + componentType;
        if (component != nullptr) {
            component->gameObject = this;
            component->deserialize(componentJson);
        }
    }
    for (auto& childJson : json["children"]) {
        GameObject* child = addChild(childJson["name"].get<std::string>().c_str());
        child->parent = this;
        child->deserialize(childJson);
    }
}
