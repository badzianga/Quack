#include "Quack/Core/Engine.hpp"
#include "Quack/Core/Input.hpp"
#include "Quack/Core/Time.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/MeshRendererComponent.hpp"
#include "Quack/Scene/Scene.hpp"

constexpr const char* VERT_SHADER = "resources/shaders/global_light.vert";
constexpr const char* FRAG_SHADER = "resources/shaders/global_light.frag";

class Application final : public Engine {
public:
    void onCreate() override {
        accessWindow().setClearColor({0.2f, 0.3f, 0.3f, 1.f});
        accessWindow().setCursorEnabled(false);
        accessWindow().setVSyncEnabled(true);

        camera = scene.createGameObject("Camera");
        camera->addComponent<CameraComponent>();

        texture.create("resources/textures/logo.png");

        object = scene.createGameObject("Object");
        object->transform.position = glm::vec3(0.f, 0.f, -2.f);
        auto* meshRendererComponent = object->addComponent<MeshRendererComponent>();
        meshRendererComponent->mesh = Mesh::createCube();
        meshRendererComponent->shader.create(VERT_SHADER, FRAG_SHADER);
        meshRendererComponent->material.baseMap = &texture;


        auto ground = scene.createGameObject("Ground");
        ground->transform.position = glm::vec3(0.f, -0.5f, -2.f);
        ground->transform.scale = glm::vec3(8.f, 1.f, 8.f);
        auto* meshRenderer = ground->addComponent<MeshRendererComponent>();
        meshRenderer->mesh = Mesh::createPlane();
        meshRenderer->shader.create(VERT_SHADER, FRAG_SHADER);
        meshRenderer->material.baseColor = Color::Blue;

        scene.startAllGameObjects();
        lastMousePosition = Input::getMousePosition();
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

        object->transform.rotation.y += 60.f * Time::getDeltaTime();

        const glm::vec3 movement = (camera->transform.getRight() * x + camera->transform.getForward() * z) * (Time::getDeltaTime() * 12.f);

        camera->transform.position += movement;

        constexpr float mouseSensitivity = 0.25f;
        glm::vec2 mouseDelta = (Input::getMousePosition() - lastMousePosition) * mouseSensitivity;
        lastMousePosition = Input::getMousePosition();
        camera->transform.rotation.x -= mouseDelta.y;
        camera->transform.rotation.x = glm::clamp(camera->transform.rotation.x, -89.f, 89.f);
        camera->transform.rotation.y += mouseDelta.x;

        timeSum += Time::getDeltaTime();
        ++fps;
        if (timeSum > 1.f) {
            printf("FPS: %d\n", fps);
            timeSum = 0.f;
            fps = 0;
        }
    }

    void onDestroy() override {
        texture.destroy();
    }
private:
    Scene scene;
    GameObject* camera = nullptr;
    GameObject* object = nullptr;
    Texture texture;
    glm::vec2 lastMousePosition{ 0.f };
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
