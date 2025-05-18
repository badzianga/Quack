#include "Quack/Scene/SceneManager.hpp"
#include "Quack/Utils/Logger.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

bool SceneManager::saveScene(const char* filepath) {
    if (filepath != nullptr) {
        m_sceneFilePath.assign(filepath);
        Logger::debug("Saved scene to defined filepath: " + std::string(filepath));
    }
    else if (m_sceneFilePath.empty()) {
        m_sceneFilePath = currentScene.name + ".json";
        Logger::debug("Saved scene to default file: " + std::string(m_sceneFilePath));
    }

    std::ofstream file(m_sceneFilePath);
    if (!file.is_open()) {
        Logger::error("Failed to open file: " + std::string(m_sceneFilePath));
        return false;
    }

    nlohmann::json json;
    json["name"] = currentScene.name;

    file << json.dump(4);
    file.close();

    Logger::debug("Saved scene to file: " + std::string(m_sceneFilePath));
    return true;
}

bool SceneManager::loadScene(const char* filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        Logger::error("Failed to open file: " + std::string(filepath));
        return false;
    }

    nlohmann::json json;
    file >> json;
    file.close();

    currentScene.name = json["name"];
    m_sceneFilePath.assign(filepath);

    Logger::debug("Loaded scene from file: " + std::string(filepath));

    return true;
}
