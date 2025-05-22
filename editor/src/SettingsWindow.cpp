#include "SettingsWindow.hpp"
#include "Quack/Core/Window.hpp"
#include <imgui.h>

void SettingsWindow::show(const Window& editorWindow) {
    if (!visible) return;

    constexpr int flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking;
    ImGui::Begin("Settings", &visible, flags);

    ImGui::Checkbox("VSync", &vSyncEnabled);
    editorWindow.setVSyncEnabled(vSyncEnabled);

    static bool wireframeMode = false;
    ImGui::Checkbox("Wireframe Mode", &wireframeMode);
    editorWindow.setWireframeModeEnabled(wireframeMode);

    ImGui::ColorEdit4("Clear Color", &clearColor.r);
    editorWindow.setClearColor(clearColor);

    ImGui::End();
}
