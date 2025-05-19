#include "Quack/Scene/SceneManager.hpp"
#include "Quack/Utils/Logger.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

bool SceneManager::saveScene(const char* filepath) {
    if (filepath != nullptr) {
        m_sceneFilePath.assign(filepath);
        Logger::debug("Saving scene to defined filepath: " + std::string(filepath));
    }
    else if (m_sceneFilePath.empty()) {
        m_sceneFilePath = currentScene.name + ".json";
        Logger::debug("Saving scene to default file: " + std::string(m_sceneFilePath));
    }

    std::ofstream file(m_sceneFilePath);
    if (!file.is_open()) {
        Logger::error("Failed to open file: " + std::string(m_sceneFilePath));
        return false;
    }

    nlohmann::json json = currentScene.serialize();

    file << json.dump(2);
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

    currentScene.deserialize(json);
    m_sceneFilePath.assign(filepath);

    Logger::debug("Loaded scene from file: " + std::string(filepath));

    return true;
}

bool SceneManager::isFileSpecified() const {
    return !m_sceneFilePath.empty();
}
