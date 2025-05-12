#include "Quack/Core.hpp"
#include "Quack/Graphics/Framebuffer.hpp"
#include "Quack/Scene.hpp"
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
                if (ImGui::MenuItem("New Scene", "Ctrl+N", false, false)) { }
                if (ImGui::MenuItem("Open Scene", "Ctrl+O", false, false)) { }
                if (ImGui::MenuItem("Save", "Ctrl+S", false, false)) { }
                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S", false, false)) { }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {
                    stop();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "Ctrl+Z", false, false)) { }
                if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) { }
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

            if (ImGui::BeginMenu("Component")) {
                bool allowAdd = selectedObject != nullptr;

                if (ImGui::MenuItem("MeshRenderer", nullptr, false, allowAdd)) {
                    selectedObject->addComponent<MeshRendererComponent>();
                }
                if (ImGui::MenuItem("Camera", nullptr, false, allowAdd)) {
                    selectedObject->addComponent<CameraComponent>();
                }
                if (ImGui::MenuItem("Script", nullptr, false, allowAdd)) {
                    selectedObject->addComponent<ScriptComponent>();
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

        ImGui::Text("Draw Calls: %zu", Stats::drawCalls);
        ImGui::Text("Vertices: %zu", Stats::vertices);
        ImGui::Text("Triangles: %zu", Stats::triangles);

        ImGui::End();

        Stats::drawCalls = 0;
        Stats::vertices = 0;
        Stats::triangles = 0;
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

        // TODO: iterate through all components and add them to Properties
        // now, only first Component of each type will be displayed
        if (selectedObject->hasComponent<MeshRendererComponent>()) {
            auto* meshRenderer = selectedObject->getComponent<MeshRendererComponent>();
            if (ImGui::CollapsingHeader("MeshRendererComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
                if (ImGui::BeginPopupContextItem("MeshRendererContext")) {
                    if (ImGui::MenuItem("Delete")) {
                        selectedObject->removeComponent<MeshRendererComponent>();
                    }
                    ImGui::EndPopup();
                }
                ImGui::Checkbox("Enabled", &meshRenderer->enabled);
                ImGui::ColorEdit3("Base Color", &meshRenderer->material.baseColor.r);
            }
        }

        // TODO: in editor, update only MeshRendererComponent
        // TODO: select which camera is currently used
        if (selectedObject->hasComponent<CameraComponent>()) {
            auto* camera = selectedObject->getComponent<CameraComponent>();
            if (ImGui::CollapsingHeader("CameraComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
                if (ImGui::BeginPopupContextItem("CameraContext")) {
                    if (ImGui::MenuItem("Delete")) {
                        selectedObject->removeComponent<CameraComponent>();
                    }
                    ImGui::EndPopup();
                }
                ImGui::Checkbox("Enabled", &camera->enabled);
                const char *projectionTypes[] = { "Perspective", "Orthographic" };
                int currentProjection = static_cast<int>(camera->projectionType);
                if (ImGui::Combo("Projection Type", &currentProjection, projectionTypes, IM_ARRAYSIZE(projectionTypes))) {
                    camera->projectionType = static_cast<CameraComponent::ProjectionType>(currentProjection);
                }
                if (camera->projectionType == CameraComponent::ProjectionType::Perspective) {
                    ImGui::DragFloat("FOV", &camera->fieldOfView, 0.1f, 1.f, 179.f);
                }
                else {
                    ImGui::DragFloat("Ortho Size", &camera->orthoSize, 0.1f);
                }
                ImGui::DragFloat("Near Clip", &camera->nearClip, 0.1f);
                ImGui::DragFloat("Far Clip", &camera->farClip, 0.1f);
                ImGui::DragFloat("Aspect Ratio", &camera->aspectRatio, 0.01f);
            }
        }

        if (selectedObject->hasComponent<ScriptComponent>()) {
            if (ImGui::CollapsingHeader("ScriptComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
                if (ImGui::BeginPopupContextItem("ScriptContext")) {
                    if (ImGui::MenuItem("Delete")) {
                        selectedObject->removeComponent<ScriptComponent>();
                    }
                    ImGui::EndPopup();
                }
                ImGui::Checkbox("Enabled", &selectedObject->getComponent<ScriptComponent>()->enabled);
                ImGui::InputText("Script Path", &selectedObject->getComponent<ScriptComponent>()->scriptPath);
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
