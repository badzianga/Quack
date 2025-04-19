#include "Quack/Core/Engine.hpp"
#include "Quack/Core/Input.hpp"
#include "Quack/Core/Time.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/MeshRendererComponent.hpp"
#include "Quack/Scene/Scene.hpp"

class Application final : public Engine {
public:
    void onCreate() override {
        accessWindow().setClearColor({0.2f, 0.3f, 0.3f, 1.f});
        accessWindow().setCursorEnabled(false);
        accessWindow().setVSyncEnabled(false);

        camera = scene.createGameObject("Camera");
        camera->addComponent<CameraComponent>();

        object = scene.createGameObject("Object");
        object->getComponent<TransformComponent>()->position = glm::vec3(0.f, 0.f, -2.f);
        auto* meshRendererComponent = object->addComponent<MeshRendererComponent>();
        meshRendererComponent->mesh = Mesh::createCube();
        meshRendererComponent->shader.create("resources/shaders/unlit.vert", "resources/shaders/unlit.frag");
        meshRendererComponent->material.baseColor = Color::Blue;

        auto ground = scene.createGameObject("Ground");
        ground->getComponent<TransformComponent>()->position = glm::vec3(0.f, -0.5f, -2.f);
        ground->getComponent<TransformComponent>()->scale = glm::vec3(8.f, 1.f, 8.f);
        auto* meshRenderer = ground->addComponent<MeshRendererComponent>();
        meshRenderer->mesh = Mesh::createPlane();
        meshRenderer->shader.create("resources/shaders/unlit.vert", "resources/shaders/unlit.frag");
        meshRenderer->material.baseColor = Color{ 0.f, 0.6f, 0.1f, 1.f };

        scene.startAllGameObjects();
        lastX = Input::getMouseX();
        lastY = Input::getMouseY();
    }

    void onUpdate() override {
        scene.updateAllGameObjects();

        if (Input::isKeyPressed(Keyboard::Key::Escape) || Input::isKeyPressed(Keyboard::Key::Q)) {
            stop();
        }

        float x = 0;
        if (Input::isKeyDown(Keyboard::Key::A)) {
            x = -1;
        }
        else if (Input::isKeyDown(Keyboard::Key::D)) {
            x = 1;
        }
        float z = 0;
        if (Input::isKeyDown(Keyboard::Key::W)) {
            z = 1;
        }
        else if (Input::isKeyDown(Keyboard::Key::S)) {
            z = -1;
        }

        object->getComponent<TransformComponent>()->rotation.y += 60.f * Time::getDeltaTime();

        const auto cameraTransform = camera->getComponent<TransformComponent>();
        const glm::vec3 movement = (cameraTransform->getRight() * x + cameraTransform->getForward() * z) * (Time::getDeltaTime() * 12.f);

        cameraTransform->position += movement;

        constexpr float mouseSensitivity = 0.25f;
        float deltaX = (Input::getMouseX() - lastX) * mouseSensitivity;
        float deltaY = (Input::getMouseY() - lastY) * mouseSensitivity;
        lastX = Input::getMouseX();
        lastY = Input::getMouseY();
        cameraTransform->rotation.x -= deltaY;
        cameraTransform->rotation.x = glm::clamp(cameraTransform->rotation.x, -89.f, 89.f);
        cameraTransform->rotation.y += deltaX;

        timeSum += Time::getDeltaTime();
        ++fps;
        if (timeSum > 1.f) {
            printf("FPS: %d\n", fps);
            timeSum = 0.f;
            fps = 0;
        }
    }

    void onDestroy() override {}
private:
    Scene scene;
    GameObject* camera = nullptr;
    GameObject* object = nullptr;
    float lastX = 0;
    float lastY = 0;
    float timeSum = 0.f;
    int fps = 0;
};

int main() {
    Application app;

    if (app.create(1024, 768, "Quack Engine")) {
        app.start();
    }

    app.destroy();

    return 0;
}
