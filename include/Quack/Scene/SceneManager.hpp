#ifndef QUACK_SCENE_MANAGER_HPP
#define QUACK_SCENE_MANAGER_HPP
#include "Quack/Scene/Scene.hpp"
#include <string>

class SceneManager {
public:
    bool saveScene(const char* filepath = nullptr);
    bool loadScene(const char* filepath);
    [[nodiscard]] bool isFileSpecified() const;

    // TODO: temporary
    void clear();

    Scene currentScene;
private:
    std::string m_sceneFilePath;
};

#endif //QUACK_SCENE_MANAGER_HPP
