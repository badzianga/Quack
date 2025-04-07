#include "Quack/Core/Engine.hpp"
#include <iostream>

class Application final : public Engine {
public:
    void onCreate() override {
        std::cout << "Application created\n";
    }

    void onUpdate() override {
        std::cout << "Application updated\n";
    }

    void onDestroy() override {
        std::cout << "Application destroyed\n";
    }
};

int main() {
    Application app;

    if (app.create()) {
        app.start();
    }

    app.destroy();

    return 0;
}
