#ifndef QUACK_EDITOR_PROJECT_MANAGER_HPP
#define QUACK_EDITOR_PROJECT_MANAGER_HPP
#include "Quack/Core/Engine.hpp"
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

struct RecentProject {
    std::string name;
    std::string path;
};

class ProjectManager final : public Engine {
public:
    void onCreate() override;
    void onUpdate() override;
    void onDestroy() override;

    [[nodiscard]] fs::path getPathToProject() const;
private:
    void createQuackConfigDir() const;
    void createRecentProjectsFile() const;
    void loadRecentProjects();
    void saveRecentProjects() const;

    fs::path m_pathToProject;
    const fs::path m_quackConfigDir{ std::string(std::getenv("HOME")) + "/.quack" };
    const fs::path m_recentProjectsFilePath = fs::path(m_quackConfigDir) / "recent_projects.json";
    std::vector<RecentProject> m_recentProjects;
    bool m_newProjectWindowOpen = false;
    std::string m_newProjectName;
    std::string m_newProjectPath;
    std::string m_createProjectError;
};

#endif //QUACK_EDITOR_PROJECT_MANAGER_HPP
