#include "Quack/Core/Engine.hpp"
#include "Quack/Core/Input.hpp"
#include "Quack/Core/Time.hpp"
#include "Quack/Scene/MeshRendererComponent.hpp"
#include "Quack/Scene/Scene.hpp"

class Application final : public Engine {
public:
    void onCreate() override {
        setWindowClearColor(0.2f, 0.3f, 0.3f, 1.f);

        camera = scene.createGameObject("Camera");
        camera->addComponent<CameraComponent>();

        triangle = scene.createGameObject("Triangle");
        triangle->getComponent<TransformComponent>()->position = glm::vec3(0, 0, -2);
        auto* meshRendererComponent = triangle->addComponent<MeshRendererComponent>();

        meshRendererComponent->mesh.create(
            {
                {{-0.5f, -0.5f, 0.0f}},
                {{0.5f, -0.5f, 0.0f}},
                {{0.0f,  0.5f, 0.0f}}
            },
            {
                0, 1, 2
            }
        );
        meshRendererComponent->shader.create("resources/shaders/universal.vert", "resources/shaders/universal.frag");

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

        triangle->getComponent<TransformComponent>()->rotation.z -= 60.f * Time::getDeltaTime();

        const auto cameraTransform = camera->getComponent<TransformComponent>();
        const glm::vec3 movement = (cameraTransform->getRight() * x + cameraTransform->getForward() * z) * (Time::getDeltaTime() * 12.f);

        cameraTransform->position += movement;
    }

    void onDestroy() override {
    }
private:
    Scene scene;
    GameObject* camera = nullptr;
    GameObject* triangle = nullptr;
};

int main() {
    Application app;

    if (app.create()) {
        app.start();
    }

    app.destroy();

    return 0;
}
