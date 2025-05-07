#include "Quack/Core/Engine.hpp"
#include "Quack/Graphics/Framebuffer.hpp"
#include "ImGuiConfig.hpp"
#include <imgui.h>

class Editor final : public Engine {
    void onCreate() override {
        ImGuiConfig::Init(accessWindow().getHandle());

        fb.create(1280, 720);
        accessWindow().setClearColor({ 0.9f, 1.f, 0.f, 1.f });
        accessWindow().setVSyncEnabled(true);
    }

    void onUpdate() override {
        ImGuiConfig::BeginFrame();

        RenderScene();
        ShowMainMenuBar();
        ShowSceneWindow();
        ShowEngineStatsWindow();
        ShowSceneHierarchyWindow();
        ShowPropertiesWindow();
        ShowContentBrowserWindow();

        ImGuiConfig::EndFrame();
    }

    void onDestroy() override {
        ImGuiConfig::Shutdown();
    }

    void RenderScene() const {
        fb.bind();
        fb.clear();
        fb.unbind();
        accessWindow().applyThisViewportSize();
    }

    void ShowMainMenuBar() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Scene")) { /* Handle new scene */ }
                if (ImGui::MenuItem("Open Scene")) { /* Handle open scene */ }
                if (ImGui::MenuItem("Save Scene")) { /* Handle save scene */ }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {
                    stop();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* Handle undo */ }
                if (ImGui::MenuItem("Redo", "Ctrl+Y")) { /* Handle redo */ }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void ShowSceneWindow() const {
        ImGui::Begin("Scene");

        ImGui::Image(fb.getTextureID(), { fb.getSize().x / 1.5f, fb.getSize().y / 1.5f });

        ImGui::End();
    }

    void ShowEngineStatsWindow() const {
        (void) fb;
        ImGui::Begin("Engine Stats");

        const ImGuiIO& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        ImGui::Separator();

        ImGui::Text("Draw Calls: %d", 10);
        ImGui::Text("Vertices: %d", 648);
        ImGui::Text("Triangles: %d", 1200);

        ImGui::End();
    }

    void ShowSceneHierarchyWindow() const {
        (void) fb;
        ImGui::Begin("Scene Hierarchy");

        // Example scene hierarchy
        if (ImGui::TreeNode("Scene")) {
            if (ImGui::TreeNode("Main Camera")) {
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Directional Light")) {
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Environment")) {
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Game Objects")) {
                if (ImGui::TreeNode("Player")) {
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("Enemies")) {
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        ImGui::End();
    }

    void ShowPropertiesWindow() const {
        (void) fb;
        ImGui::Begin("Properties");

        // Example properties for a selected object
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
            static float position[3] = { 0.f, 0.f, 0.f };
            static float rotation[3] = { 0.f, 0.f, 0.f };
            static float scale[3] = { 1.f, 1.f, 1.f };

            ImGui::DragFloat3("Position", position, 0.1f);
            ImGui::DragFloat3("Rotation", rotation, 1.f);
            ImGui::DragFloat3("Scale", scale, 0.1f);
        }

        if (ImGui::CollapsingHeader("Mesh Renderer", ImGuiTreeNodeFlags_DefaultOpen)) {
            static bool enabled = true;
            ImGui::Checkbox("Enabled", &enabled);

            // Material selector would go here
            ImGui::Text("Material: Default Material");
        }

        ImGui::End();
    }

    void ShowContentBrowserWindow() const {
        (void) fb;
        ImGui::Begin("Content Browser");

        // Example folder structure
        if (ImGui::TreeNode("Assets")) {
            if (ImGui::TreeNode("Models")) {
                ImGui::Text("cube.obj");
                ImGui::Text("fox.obj");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Textures")) {
                ImGui::Text("logo.png");
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        ImGui::End();
    }

    Framebuffer fb;
};

int main() {
    Editor editor;
    if (editor.create(1600, 900, "Quack Editor")) {
        editor.start();
    }
    editor.destroy();
    return 0;
}
