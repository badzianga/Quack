#include "Quack/Core.hpp"
#include "Quack/Graphics/Framebuffer.hpp"
#include "Quack/Scene.hpp"
#include "Quack/Utils/Logger.hpp"
#include "ImGuiConfig.hpp"
#include <filesystem>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <ImGuiFileDialog.h>

namespace fs = std::filesystem;

constexpr auto VERT_SHADER = "resources/shaders/global_light.vert";
constexpr auto FRAG_SHADER = "resources/shaders/global_light.frag";

class Editor final : public Engine {
    void onCreate() override {
        ImGuiConfig::Init(accessWindow().getHandle());

        sceneFramebuffer.create(1280, 720);
        accessWindow().setClearColor({ 0.1f, 0.1f, 0.2f, 1.f });
        accessWindow().setVSyncEnabled(false);

        editorCameraComponent = editorCamera.addComponent<CameraComponent>();
        editorCamera.transform.position = Vector3(-2.f, 2.f / 1.5f, 2.f);
        editorCamera.transform.rotation = { -25.02f, 45.f, 0.f };
        editorCameraComponent->aspectRatio = 16.f / 9.f;
        editorCamera.startAllComponents();

        GlobalLight::direction = { 0.7f, -1.f, -0.5f };

        Logger::setMinLogLevel(Logger::LogLevel::Debug);

        // Create Assets folder in the same directory as editor executable if not exists
        if (!fs::exists("Assets")) {
            try {
                fs::create_directory("Assets");
            }
            catch (const fs::filesystem_error& e) {
                Logger::error("Failed to create Assets directory: " + std::string(e.what()));
            }
        }
    }

    void onUpdate() override {
        ImGuiConfig::BeginFrame();

        HandleKeyboardShortcuts();
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
        DestroySceneGameObjects();
    }

    void HandleKeyboardShortcuts() {
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
            if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
                if (ImGui::IsKeyPressed(ImGuiKey_S)) {
                    OpenSaveSceneFileDialog();
                }
            }
            if (ImGui::IsKeyPressed(ImGuiKey_S)) {
                if (sceneManager.isFileSpecified()) {
                    sceneManager.saveScene();
                }
                else {
                    OpenSaveSceneFileDialog();
                }
            }
            if (ImGui::IsKeyPressed(ImGuiKey_O)) {
                OpenLoadSceneFileDialog();
            }
            if (ImGui::IsKeyPressed(ImGuiKey_N)) {
                sceneManager.clear();
                selectedObject = nullptr;
                toDelete = nullptr;
                parentOfToDelete = nullptr;
            }
        }
    }

    void DestroySceneGameObjects() {
        for (auto& object : sceneManager.currentScene.getAllGameObjects()) {
            if (object->hasComponent<MeshRendererComponent>()) {
                auto* meshRenderer = object->getComponent<MeshRendererComponent>();
                meshRenderer->mesh.destroy();
                meshRenderer->shader.destroy();

                DestroyChildren(object);
            }
        }
    }

    static void DestroyChildren(const std::unique_ptr<GameObject>& parent) {
        for (auto& child : parent->getChildren()) {
            auto* meshRenderer = child->getComponent<MeshRendererComponent>();
            meshRenderer->mesh.destroy();
            meshRenderer->shader.destroy();

            DestroyChildren(child);
        }
    }

    void RenderScene() const {
        sceneFramebuffer.bind();

        sceneFramebuffer.clear();

        editorCamera.updateAllComponents();
        sceneManager.currentScene.updateAllGameObjects();

        sceneFramebuffer.unbind();
        accessWindow().applyThisViewportSize();
    }

    static void OpenSaveSceneFileDialog() {
        IGFD::FileDialogConfig config;
        config.path = ".";
        config.countSelectionMax = 1;
        config.flags = ImGuiFileDialogFlags_Modal;
        ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlg", "Save Scene", ".json", config);
    }

    static void OpenLoadSceneFileDialog() {
        IGFD::FileDialogConfig config;
        config.path = ".";
        config.countSelectionMax = 1;
        config.flags = ImGuiFileDialogFlags_Modal;
        ImGuiFileDialog::Instance()->OpenDialog("LoadFileDlg", "Open Scene", ".json", config);
    }

    void ShowMainMenuBar() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Scene", "Ctrl+N")) {
                    sceneManager.clear();
                    selectedObject = nullptr;
                    toDelete = nullptr;
                    parentOfToDelete = nullptr;
                }
                if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {
                    OpenLoadSceneFileDialog();
                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) {
                    if (sceneManager.isFileSpecified()) {
                        sceneManager.saveScene();
                    }
                    else {
                        OpenSaveSceneFileDialog();
                    }
                }
                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
                    OpenSaveSceneFileDialog();
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {
                    stop();
                }
                ImGui::EndMenu();
            }

            if (ImGuiFileDialog::Instance()->Display("SaveFileDlg", ImGuiWindowFlags_NoCollapse, { 800, 500 })) {
                if (ImGuiFileDialog::Instance()->IsOk()) {
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

                    sceneManager.saveScene(filePathName.c_str());
                }
                ImGuiFileDialog::Instance()->Close();
            }

            if (ImGuiFileDialog::Instance()->Display("LoadFileDlg", ImGuiWindowFlags_NoCollapse, { 800, 500 })) {
                if (ImGuiFileDialog::Instance()->IsOk()) {
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

                    // TODO: not a great solution, but it will work for now
                    DestroySceneGameObjects();
                    sceneManager.clear();
                    selectedObject = nullptr;
                    toDelete = nullptr;
                    parentOfToDelete = nullptr;

                    sceneManager.loadScene(filePathName.c_str());
                }
                ImGuiFileDialog::Instance()->Close();
            }

            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "Ctrl+Z", false, false)) { }
                if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) { }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("GameObject")) {
                if (ImGui::MenuItem("Create Empty")) {
                    if (selectedObject != nullptr) {
                        selectedObject = selectedObject->addChild();
                    }
                    else {
                        selectedObject = sceneManager.currentScene.createGameObject();
                    }
                }
                if (ImGui::MenuItem("Create Cube")) {
                    MeshRendererComponent* meshRenderer = nullptr;
                    if (selectedObject != nullptr) {
                        selectedObject = selectedObject->addChild("Cube");
                    }
                    else {
                        selectedObject = sceneManager.currentScene.createGameObject("Cube");
                    }
                    meshRenderer = selectedObject->addComponent<MeshRendererComponent>();
                    meshRenderer->mesh = Mesh::createCube();
                    meshRenderer->shader.create(VERT_SHADER, FRAG_SHADER);
                }
                if (ImGui::MenuItem("Create Sphere")) {
                    MeshRendererComponent* meshRenderer = nullptr;
                    if (selectedObject != nullptr) {
                        selectedObject = selectedObject->addChild("Sphere");
                    }
                    else {
                        selectedObject = sceneManager.currentScene.createGameObject("Sphere");
                    }
                    meshRenderer = selectedObject->addComponent<MeshRendererComponent>();
                    meshRenderer->mesh = Mesh::createSphere();
                    meshRenderer->shader.create(VERT_SHADER, FRAG_SHADER);
                }
                if (ImGui::MenuItem("Create Plane")) {
                    MeshRendererComponent* meshRenderer = nullptr;
                    if (selectedObject != nullptr) {
                        selectedObject = selectedObject->addChild("Plane");
                    }
                    else {
                        selectedObject = sceneManager.currentScene.createGameObject("Plane");
                    }
                    meshRenderer = selectedObject->addComponent<MeshRendererComponent>();
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

    static void ShowEngineStatsWindow() {
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

    void ShowChildrenInSceneHierarchy(std::unique_ptr<GameObject>& parent) {
        int flags = 0;
        if (parent->getChildren().empty()) {
            flags |= ImGuiTreeNodeFlags_Leaf;
        }
        else {
            flags |= ImGuiTreeNodeFlags_DefaultOpen;
            flags |= ImGuiTreeNodeFlags_OpenOnArrow;
        }
        if (parent.get() == selectedObject) {
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        if (ImGui::TreeNodeEx(parent->name.c_str(), flags)) {
            if (ImGui::IsItemClicked()) {
                selectedObject = parent.get();
            }

            if (ImGui::BeginPopupContextItem()) {
                if (ImGui::MenuItem("Delete")) {
                    toDelete = parent.get();
                    parentOfToDelete = parent->parent;
                }
                ImGui::EndPopup();
            }

            for (auto& child : parent->getChildren()) {
                ShowChildrenInSceneHierarchy(child);
            }

            ImGui::TreePop();
        }
    }

    void ShowSceneHierarchyWindow() {
        ImGui::Begin("Scene Hierarchy");

        if (ImGui::TreeNodeEx(sceneManager.currentScene.name.c_str(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) {
            if (ImGui::IsItemClicked()) {
                selectedObject = nullptr;
            }

            for (auto &child: sceneManager.currentScene.getAllGameObjects()) {
                ShowChildrenInSceneHierarchy(child);


            }
            ImGui::TreePop();

            if (toDelete != nullptr) {
                // for now, always unset selected object when deleting
                selectedObject = nullptr;

                // TODO: temporary, destroy MeshRendererComponent resources
                if (toDelete->hasComponent<MeshRendererComponent>()) {
                    auto* meshRenderer = toDelete->getComponent<MeshRendererComponent>();
                    meshRenderer->mesh.destroy();
                    meshRenderer->shader.destroy();
                }

                // TODO: I don't know if this method of deleting is good, but it works
                if (parentOfToDelete != nullptr) {
                    parentOfToDelete->removeChild(toDelete);
                    parentOfToDelete = nullptr;
                }
                else {
                    sceneManager.currentScene.removeGameObject(toDelete);
                }
                toDelete = nullptr;
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
            // TODO: this should probably be in core instead of editor
            for (int i = 0; i < 3; ++i) {
                while (transform.rotation[i] > 360.f) {
                    transform.rotation[i] -= 360.f;
                }
                while (transform.rotation[i] < 360.f) {
                    transform.rotation[i] += 360.f;
                }
            }
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
                // TODO: without '#' there is a name conflict with previous "Enabled" checkbox label
                ImGui::Checkbox("#Enabled", &selectedObject->getComponent<ScriptComponent>()->enabled);
                ImGui::InputText("Script Path", &selectedObject->getComponent<ScriptComponent>()->scriptPath);

                if (ImGui::BeginDragDropTarget()) {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_PATH")) {
                        auto* droppedPath = static_cast<const char*>(payload->Data);
                        selectedObject->getComponent<ScriptComponent>()->scriptPath = droppedPath;
                    }
                    ImGui::EndDragDropTarget();
                }

                // TODO: temporary
                if (ImGui::Button("Start")) {
                    auto* script = selectedObject->getComponent<ScriptComponent>();
                    script->start();
                }
            }
        }

        ImGui::End();
    }

    static void ShowDirectoryTree(const fs::path& path) {
        for (const auto& entry : fs::directory_iterator(path)) {
            const auto& p = entry.path();
            if (entry.is_directory()) {
                if (ImGui::TreeNodeEx(p.filename().string().c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
                    ShowDirectoryTree(p);
                    ImGui::TreePop();
                }
            } else {
                ImGui::TreeNodeEx(p.filename().string().c_str(), ImGuiTreeNodeFlags_Leaf);

                if (ImGui::BeginDragDropSource()) {
                    std::string relativePath = "Assets/" + fs::relative(p, fs::current_path() / "Assets").string();
                    ImGui::SetDragDropPayload("CONTENT_BROWSER_PATH", relativePath.c_str(), relativePath.size() + 1);
                    ImGui::Text("%s", relativePath.c_str());
                    ImGui::EndDragDropSource();
                }

                ImGui::TreePop();
            }
        }
    }

    static void ShowContentBrowserWindow() {
        ImGui::Begin("Content Browser");

        fs::path rootPath = fs::current_path() / "Assets";

        if (ImGui::TreeNodeEx("Assets", ImGuiTreeNodeFlags_DefaultOpen)) {
            ShowDirectoryTree(rootPath);
            ImGui::TreePop();
        }

        ImGui::End();
    }

    Framebuffer sceneFramebuffer;
    SceneManager sceneManager;
    GameObject editorCamera;
    CameraComponent* editorCameraComponent = nullptr;
    GameObject* selectedObject = nullptr;
    GameObject* toDelete = nullptr;
    GameObject* parentOfToDelete = nullptr;
};

int main() {
    Editor editor;
    if (editor.create(1600, 900, "Quack Editor")) {
        editor.start();
    }
    editor.destroy();
    return 0;
}
