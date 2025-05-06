#include "Quack/Core/Engine.hpp"
#include "ImGuiConfig.hpp"
#include <imgui.h>

class Editor final : public Engine {
    void onCreate() override {
        ImGuiConfig::Init(accessWindow().getHandle());
    }

    void onUpdate() override {
        ImGuiConfig::BeginFrame();

        ImGui::Begin("Hello, world!");
        {
            ImGuiIO& io = ImGui::GetIO();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        }
        ImGui::End();

        ImGuiConfig::EndFrame();
    }

    void onDestroy() override {
        ImGuiConfig::Shutdown();
    }
};

int main() {
    Editor editor;
    if (editor.create(1600, 900, "Quack Editor")) {
        editor.start();
    }
    editor.destroy();
    return 0;
}
