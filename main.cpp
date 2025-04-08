#include "Quack/Core/Engine.hpp"
#include "Quack/Core/Input.hpp"

class Application final : public Engine {
public:
    void onCreate() override {}

    void onUpdate() override {
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
