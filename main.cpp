#include "Quack/Core/Engine.hpp"
#include "Quack/Core/Input.hpp"
#include "Quack/Graphics/Mesh.hpp"
#include "Quack/Graphics/Shader.hpp"

class Application final : public Engine {
public:
    void onCreate() override {
        mesh.create(
            {
                {{-0.5f, -0.5f, 0.0f}},
                {{0.5f, -0.5f, 0.0f}},
                {{0.0f,  0.5f, 0.0f}}
            },
            {
                0, 1, 2
            }
        );
        shader.create("resources/shaders/position.vert", "resources/shaders/position.frag");

        setWindowClearColor(0.2f, 0.3f, 0.3f, 1.f);
    }

    void onUpdate() override {
        mesh.draw(shader);

        if (Input::isKeyPressed(Keyboard::Key::Escape) || Input::isKeyPressed(Keyboard::Key::Q)) {
            stop();
        }
    }

    void onDestroy() override {
        shader.destroy();
        mesh.destroy();
    }
private:
    Shader shader;
    Mesh mesh;
};

int main() {
    Application app;

    if (app.create()) {
        app.start();
    }

    app.destroy();

    return 0;
}
