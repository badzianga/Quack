#include "Quack/Core/Engine.hpp"
#include "Quack/Core/Input.hpp"
#include "Quack/Core/Time.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/MeshRendererComponent.hpp"
#include "Quack/Scene/Scene.hpp"

class Application final : public Engine {
public:
    void onCreate() override {
        setWindowClearColor(0.2f, 0.3f, 0.3f, 1.f);

        camera = scene.createGameObject("Camera");
        camera->addComponent<CameraComponent>();

        object = scene.createGameObject("Object");
        object->getComponent<TransformComponent>()->position = glm::vec3(0.f, 0.f, -2.f);
        auto* meshRendererComponent = object->addComponent<MeshRendererComponent>();

        meshRendererComponent->mesh = Mesh::createCube();
        meshRendererComponent->shader.create("resources/shaders/universal.vert", "resources/shaders/universal.frag");
        meshRendererComponent->material.colorMap = { 0.f, 0.f, 1.f, 1.f };

        scene.startAllGameObjects();
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
    }

    void onDestroy() override {
    }
private:
    Scene scene;
    GameObject* camera = nullptr;
    GameObject* object = nullptr;
};

int main() {
    Application app;

    if (app.create()) {
        app.start();
    }

    app.destroy();

    return 0;
}
