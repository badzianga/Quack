#include "Quack/Core/Engine.hpp"

class Application final : public Engine {
public:
    void onCreate() override {}

    void onUpdate() override {}

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
