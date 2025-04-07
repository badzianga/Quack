# Quack Engine

Quack Engine is a simple 3D game engine created using C++ and OpenGL.

## Usage
```C++
#include <Quack/Core/Engine.hpp>

class Application final : public Engine {
public:
    void onCreate() override {
        // This code will be executed during creation.
    }

    void onUpdate() override {
        // This code will be executed every frame.
    }

    void onDestroy() override {
        // This code will be executed during destruction.
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
```

## Future improvements
- Error handling
- Logger
- Time scaling
- Fixed timestep
- Mouse inputs
- Action mapping
- Mouse delta
- Gamepad support
