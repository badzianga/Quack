#include "StatsWindow.hpp"
#include "Quack/Core/Stats.hpp"
#include <imgui.h>

void StatsWindow::show() {
    ImGui::Begin("Engine Stats");

    const ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.f / io.Framerate, io.Framerate);

    ImGui::Separator();

    ImGui::Text("Draw Calls: %zu", Stats::drawCalls);
    ImGui::Text("Vertices: %zu", Stats::vertices);
    ImGui::Text("Triangles: %zu", Stats::triangles);

    ImGui::End();

    Stats::drawCalls = 0;
    Stats::vertices = 0;
    Stats::triangles = 0;
}
