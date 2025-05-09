#include "Quack/Core/Engine.hpp"
#include "Quack/Core/Input.hpp"
#include "Quack/Core/Time.hpp"
#include "Quack/Graphics/Framebuffer.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/MeshRendererComponent.hpp"
#include "Quack/Scene/Scene.hpp"
#include "Quack/Utils/Logger.hpp"
#include "ImGuiConfig.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>

constexpr auto VERT_SHADER = "resources/shaders/global_light.vert";
constexpr auto FRAG_SHADER = "resources/shaders/global_light.frag";

class Editor final : public Engine {
    void onCreate() override {
        ImGuiConfig::Init(accessWindow().getHandle());

        sceneFramebuffer.create(1280, 720);
        accessWindow().setClearColor({ 0.1f, 0.1f, 0.2f, 1.f });
        accessWindow().setVSyncEnabled(true);

        editorCameraComponent = editorCamera.addComponent<CameraComponent>();
        editorCamera.transform.position = Vector3(-2.f, 2.f / 1.5f, 2.f);
        editorCamera.transform.rotation = { -25.02f, 45.f, 0.f };
        editorCameraComponent->aspectRatio = 16.f / 9.f;
        editorCamera.startAllComponents();

        GlobalLight::direction = { 0.7f, -1.f, -0.5f };

        Logger::setMinLogLevel(Logger::LogLevel::Debug);
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

        // TODO: temporary, destroy scene resources
        for (auto& object : currentScene.getAllGameObjects()) {
            if (object->hasComponent<MeshRendererComponent>()) {
                auto* meshRenderer = object->getComponent<MeshRendererComponent>();
                meshRenderer->mesh.destroy();
                meshRenderer->shader.destroy();
            }
        }
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

            if (ImGui::BeginMenu("GameObject")) {
                if (ImGui::MenuItem("Create Empty")) {
                    selectedObject = currentScene.createGameObject();
                }
                if (ImGui::MenuItem("Create Cube")) {
                    selectedObject = currentScene.createGameObject("Cube");
                    auto* meshRenderer = selectedObject->addComponent<MeshRendererComponent>();
                    meshRenderer->mesh = Mesh::createCube();
                    meshRenderer->shader.create(VERT_SHADER, FRAG_SHADER);
                }
                if (ImGui::MenuItem("Create Sphere")) {
                    selectedObject = currentScene.createGameObject("Sphere");
                    auto* meshRenderer = selectedObject->addComponent<MeshRendererComponent>();
                    meshRenderer->mesh = Mesh::createSphere();
                    meshRenderer->shader.create(VERT_SHADER, FRAG_SHADER);
                }
                if (ImGui::MenuItem("Create Plane")) {
                    selectedObject = currentScene.createGameObject("Plane");
                    auto* meshRenderer = selectedObject->addComponent<MeshRendererComponent>();
                    meshRenderer->mesh = Mesh::createPlane();
                    meshRenderer->shader.create(VERT_SHADER, FRAG_SHADER);
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void ShowSceneWindow()  {
        ImGui::Begin("Scene");

        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows)) {
            constexpr float scrollSensitivity = 4.f;
            editorCameraComponent->fieldOfView -= ImGui::GetIO().MouseWheel * scrollSensitivity;
            editorCameraComponent->fieldOfView = Math::clamp(editorCameraComponent->fieldOfView, 1.f, 179.f);

            if (Input::isButtonPressed(Mouse::Button::Right)) {
                constexpr float mouseSensitivity = 0.25f;
                constexpr float cameraSpeed = 10.f;
                auto mouseDelta = ImGui::GetIO().MouseDelta;
                editorCamera.transform.rotation.x -= mouseDelta.y * mouseSensitivity;
                editorCamera.transform.rotation.x = Math::clamp(editorCamera.transform.rotation.x, -89.f, 89.f);
                editorCamera.transform.rotation.y += mouseDelta.x * mouseSensitivity;

                float x = 0;
                float z = 0;
                if (Input::isKeyDown(Keyboard::Key::A))      x = -1;
                else if (Input::isKeyDown(Keyboard::Key::D)) x = 1;
                if (Input::isKeyDown(Keyboard::Key::W))      z = 1;
                else if (Input::isKeyDown(Keyboard::Key::S)) z = -1;

                Vector3 movement = (editorCamera.transform.getRight() * x + editorCamera.transform.getForward() * z) * (Time::getDeltaTime() * cameraSpeed);
                editorCamera.transform.position += movement;
            }
        }

        // TODO: maybe scene render should be here?

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

    void ShowSceneHierarchyWindow() {
        ImGui::Begin("Scene Hierarchy");

        ImGui::SetNextItemOpen(true);
        if (ImGui::TreeNode(currentScene.name.c_str())) {
            GameObject* toDelete = nullptr;

            for (auto &child: currentScene.getAllGameObjects()) {
                if (ImGui::TreeNodeEx(child->name.c_str(), ImGuiTreeNodeFlags_Leaf)) {
                    if (ImGui::IsItemClicked()) {
                        selectedObject = child.get();
                    }

                    if (ImGui::BeginPopupContextItem()) {
                        if (ImGui::MenuItem("Delete")) {
                            toDelete = child.get();

                            ImGui::EndPopup();
                            ImGui::TreePop();
                            continue; // Skip rendering deleted object
                        }
                        ImGui::EndPopup();
                    }

                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();

            if (toDelete != nullptr) {
                if (selectedObject == toDelete) {
                    selectedObject = nullptr;
                }

                // TODO: temporary, destroy MeshRendererComponent resources
                if (toDelete->hasComponent<MeshRendererComponent>()) {
                    auto* meshRenderer = toDelete->getComponent<MeshRendererComponent>();
                    meshRenderer->mesh.destroy();
                    meshRenderer->shader.destroy();
                }

                currentScene.removeGameObject(toDelete);
            }
        }

        ImGui::End();
    }

    void ShowPropertiesWindow() const {
        ImGui::Begin("Properties");

        if (selectedObject == nullptr) {
            ImGui::End();
            return;
        }

        ImGui::Checkbox("##Active", &selectedObject->active);
        ImGui::SameLine();
        ImGui::InputText("##Name", &selectedObject->name, ImGuiInputTextFlags_EnterReturnsTrue);

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
    CameraComponent* editorCameraComponent = nullptr;
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
