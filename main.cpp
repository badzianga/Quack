#include "Quack/Core/Engine.hpp"
#include "Quack/Core/Input.hpp"
#include "src/Quack/Graphics/Renderer.hpp"

class Application final : public Engine {
public:
    void onCreate() override {}

    void onUpdate() override {
        Renderer::clear(0.2f, 0.3f, 0.3f, 1.0f);

        Renderer::drawTestTriangle();

        if (Input::isKeyPressed(Keyboard::Key::Escape) || Input::isKeyPressed(Keyboard::Key::Q)) {
            stop();
        }
    }

    void onDestroy() override {}
};

int main() {
    Application app;

    if (app.create()) {
        app.start();
    }

    app.destroy();

    return 0;
}
