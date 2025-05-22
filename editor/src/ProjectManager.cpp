#include "ProjectManager.hpp"
#include "ImGuiConfig.hpp"
#include "Quack/Utils/Logger.hpp"
#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <ImGuiFileDialog.h>
#include <nlohmann/json.hpp>

#include "FileDialog.hpp"

void ProjectManager::onCreate() {
    if (!fs::exists(m_quackConfigDir)) {
        createQuackConfigDir();
    }

    if (!fs::exists(m_recentProjectsFilePath)) {
        createRecentProjectsFile();
    }
    else {
        loadRecentProjects();
    }

    ImGuiConfig::Init(accessWindow().getHandle());
}

void ProjectManager::onUpdate() {
    ImGuiConfig::BeginFrame();
    ImGui::Begin("Project Manager");

    if (ImGui::Button("New Project")) {
        m_newProjectWindowOpen = true;
        m_newProjectName.clear();
        m_newProjectPath.clear();
        m_createProjectError.clear();
        ImGui::OpenPopup("New Project");
    }
    ImGui::SameLine();
    if (ImGui::Button("Import Project")) {
        // TODO: add config with recently opened path to .quack
        FileDialog::open("ImportProjectDlg", "Import Project", ".qproj", std::getenv("HOME"));
    }

    ImGui::Separator();

    ImGui::Text("Recent Projects");
    for (const auto& recentProject : m_recentProjects) {
        if (ImGui::Selectable(recentProject.name.c_str())) {
            m_pathToProject = recentProject.path;
            // TODO: verify somewhere that project.qproj exists
            stop();
        }
    }

    if (ImGui::BeginPopupModal("New Project", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::InputText("Project Name", &m_newProjectName, ImGuiInputTextFlags_EnterReturnsTrue);
        // TODO: add file dialog
        ImGui::InputText("Project Path", &m_newProjectPath, ImGuiInputTextFlags_EnterReturnsTrue);

        if (!m_createProjectError.empty()) {
            ImGui::TextColored({ 1.f, 0.3f, 0.3f, 1.f }, "%s", m_createProjectError.c_str());
        }

        if (ImGui::Button("Create Project")) {
            if (m_newProjectName.empty() || m_newProjectPath.empty()) {
                m_createProjectError = "Please fill all fields";
            }
            else {
                std::string projectPath = m_newProjectPath + "/" + m_newProjectName;
                if (fs::exists(projectPath)) {
                    m_createProjectError = "Project with this name already exists";
                }
                else {
                    // create project dir with content
                    fs::create_directory(projectPath);
                    m_pathToProject = projectPath + "/project.qproj";

                    std::ofstream projectFile(m_pathToProject);
                    nlohmann::json projectJson;
                    projectJson["name"] = m_newProjectName;
                    projectFile << projectJson.dump(2);
                    projectFile.close();

                    m_recentProjects.push_back({ m_newProjectName, m_pathToProject });

                    m_newProjectWindowOpen = false;
                    ImGui::CloseCurrentPopup();
                }
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            m_newProjectWindowOpen = false;
            ImGui::CloseCurrentPopup();
        };

        ImGui::EndPopup();
    }

    // TODO: verify that selected project is not imported yet
    if (ImGuiFileDialog::Instance()->Display("ImportProjectDlg", ImGuiWindowFlags_NoCollapse, { 1000, 500 })) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            m_pathToProject = filePathName;

            std::ifstream projectFile(m_pathToProject);
            nlohmann::json projectJson;
            projectFile >> projectJson;
            projectFile.close();
            std::string projectName = projectJson["name"].get<std::string>();

            m_recentProjects.push_back({ projectName, m_pathToProject });
        }
        ImGuiFileDialog::Instance()->Close();
    }

    ImGui::End();
    ImGuiConfig::EndFrame();

    if (!m_pathToProject.empty()) {
        saveRecentProjects();
        stop();
    }
}

void ProjectManager::onDestroy() {
    ImGuiConfig::Shutdown();
}

std::filesystem::path ProjectManager::getPathToProject() const {
    return m_pathToProject;
}

void ProjectManager::createQuackConfigDir() const {
    fs::create_directory(m_quackConfigDir);
    Logger::debug("Created config directory in home dir");
}

void ProjectManager::createRecentProjectsFile() const {
    std::ofstream recentProjectsFile(m_recentProjectsFilePath);
    nlohmann::json recentProjectsJson = nlohmann::json::array();

    recentProjectsFile << recentProjectsJson.dump();
    recentProjectsFile.close();
    Logger::debug("Created empty recent projects file");
}

void ProjectManager::loadRecentProjects() {
    std::ifstream recentProjectsFile(m_recentProjectsFilePath);
    nlohmann::json recentProjectsJson;
    recentProjectsFile >> recentProjectsJson;
    recentProjectsFile.close();

    for (auto& recentProjectJson : recentProjectsJson) {
        m_recentProjects.push_back({ recentProjectJson["name"], recentProjectJson["path"] });
    }
    Logger::debug("Loaded recent projects file");
}

void ProjectManager::saveRecentProjects() const {
    std::ofstream recentProjectsFile(m_recentProjectsFilePath, std::ios::out | std::ios::trunc);
    nlohmann::json recentProjectsJson = nlohmann::json::array();
    for (auto& recentProject : m_recentProjects) {
        nlohmann::json entry;
        entry["name"] = recentProject.name;
        entry["path"] = recentProject.path;
        recentProjectsJson.push_back(entry);
    }
    recentProjectsFile << recentProjectsJson.dump(2);
    recentProjectsFile.close();
    Logger::debug("Saved recent projects file");
}