#include "Quack/Core/Engine.hpp"
#include "Quack/Graphics/Framebuffer.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/Scene.hpp"
#include "ImGuiConfig.hpp"
#include <imgui.h>

#include "Quack/Scene/MeshRendererComponent.hpp"

class Editor final : public Engine {
    void onCreate() override {
        ImGuiConfig::Init(accessWindow().getHandle());

        sceneFramebuffer.create(1280, 720);
        accessWindow().setClearColor({ 0.1f, 0.1f, 0.2f, 1.f });
        accessWindow().setVSyncEnabled(false);

        editorCamera.addComponent<CameraComponent>();
        editorCamera.transform.position = Vector3(-2.f, 2.f / 1.5f, 2.f);
        editorCamera.transform.rotation = { -25.02f, 45.f, 0.f };
        editorCamera.getComponent<CameraComponent>()->aspectRatio = 16.f / 9.f;
        editorCamera.startAllComponents();

        selectedObject = currentScene.createGameObject("GameObject");
        selectedObject->addComponent<MeshRendererComponent>();
        selectedObject->getComponent<MeshRendererComponent>()->mesh = Mesh::createCube();
        selectedObject->getComponent<MeshRendererComponent>()->shader.create("resources/shaders/global_light.vert", "resources/shaders/global_light.frag");
        selectedObject->getComponent<MeshRendererComponent>()->material.baseColor = Color::Red;
        currentScene.startAllGameObjects();

        GlobalLight::direction = { 0.7f, -1.f, -0.5f };
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
        sceneFramebuffer.bind();

        sceneFramebuffer.clear();

        editorCamera.updateAllComponents();
        currentScene.updateAllGameObjects();

        sceneFramebuffer.unbind();
        accessWindow().applyThisViewportSize();
    }

    void ShowMainMenuBar() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Scene", "Ctrl+N")) { }
                if (ImGui::MenuItem("Open Scene", "Ctrl+O")) { }
                if (ImGui::MenuItem("Save", "Ctrl+S")) { }
                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) { }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {
                    stop();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "Ctrl+Z")) { }
                if (ImGui::MenuItem("Redo", "Ctrl+Y")) { }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void ShowSceneWindow() const {
        ImGui::Begin("Scene");

        ImGui::Image(
            sceneFramebuffer.getTextureID(),
            { sceneFramebuffer.getSize().x / 1.5f, sceneFramebuffer.getSize().y / 1.5f },
            { 0.f, 1.f },
            { 1.f, 0.f }
        );

        ImGui::End();
    }

    void ShowEngineStatsWindow() const {
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
        ImGui::Begin("Properties");

        if (selectedObject == nullptr) {
            ImGui::End();
            return;
        }

        ImGui::Checkbox("Active", &selectedObject->active);

        Transform& transform = selectedObject->transform;
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::DragFloat3("Position", &transform.position.x, 0.1f);
            ImGui::DragFloat3("Rotation", &transform.rotation.x, 1.f);
            ImGui::DragFloat3("Scale", &transform.scale.x, 0.1f);
        }

        if (selectedObject->hasComponent<MeshRendererComponent>()) {
            auto* meshRenderer = selectedObject->getComponent<MeshRendererComponent>();
            if (ImGui::CollapsingHeader("Mesh Renderer", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::Checkbox("Enabled", &meshRenderer->enabled);
                ImGui::ColorEdit3("Base Color", &meshRenderer->material.baseColor.r);
            }
        }

        ImGui::End();
    }

    void ShowContentBrowserWindow() const {
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

    Framebuffer sceneFramebuffer;
    Scene currentScene;
    GameObject editorCamera;
    GameObject* selectedObject = nullptr;
};

int main() {
    Editor editor;
    if (editor.create(1600, 900, "Quack Editor")) {
        editor.start();
    }
    editor.destroy();
    return 0;
}
