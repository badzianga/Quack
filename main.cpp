#include "Quack/Core/Engine.hpp"
#include "Quack/Core/Input.hpp"
#include "Quack/Scene/MeshRendererComponent.hpp"
#include "Quack/Scene/Scene.hpp"

class Application final : public Engine {
public:
    void onCreate() override {
        setWindowClearColor(0.2f, 0.3f, 0.3f, 1.f);

        GameObject* triangle = scene.createGameObject("Triangle");
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
        meshRendererComponent->shader.create("resources/shaders/position.vert", "resources/shaders/position.frag");

        scene.startAllGameObjects();
    }

    void onUpdate() override {
        scene.updateAllGameObjects();

        if (Input::isKeyPressed(Keyboard::Key::Escape) || Input::isKeyPressed(Keyboard::Key::Q)) {
            stop();
        }
    }

    void onDestroy() override {
    }
private:
    Scene scene;
};

int main() {
    Application app;

    if (app.create()) {
        app.start();
    }

    app.destroy();

    return 0;
}
