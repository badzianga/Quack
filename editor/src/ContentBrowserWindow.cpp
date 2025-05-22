#include "ContentBrowserWindow.hpp"
#include <imgui.h>

namespace fs = std::filesystem;

void ContentBrowserWindow::show() {
    ImGui::Begin("Content Browser");

    fs::path rootPath = "./Assets";

    if (ImGui::TreeNodeEx("Assets", ImGuiTreeNodeFlags_DefaultOpen)) {
        showDirectoryTree(rootPath);
        ImGui::TreePop();
    }

    ImGui::End();
}

void ContentBrowserWindow::showDirectoryTree(const fs::path& path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        const auto& p = entry.path();
        if (entry.is_directory()) {
            if (ImGui::TreeNodeEx(p.filename().string().c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
                showDirectoryTree(p);
                ImGui::TreePop();
            }
        } else {
            if (entry.path().extension() == ".meta") continue;
            ImGui::TreeNodeEx(p.filename().string().c_str(), ImGuiTreeNodeFlags_Leaf);

            if (ImGui::BeginDragDropSource()) {
                std::string pathStr = entry.path().string();
                std::string payloadType = "path" + entry.path().extension().string();
                ImGui::SetDragDropPayload(payloadType.c_str(), pathStr.c_str(), pathStr.size() + 1);
                ImGui::Text("%s", pathStr.c_str());
                ImGui::EndDragDropSource();
            }

            ImGui::TreePop();
        }
    }
}
