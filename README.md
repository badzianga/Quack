# Quack Engine

Quack Engine is a currently developed small 3D game engine created using C++ and OpenGL.

## Usage Example
```C++
#include <Quack/Core/Engine.hpp>
#include <Quack/Scene/MeshRendererComponent.hpp>
#include <Quack/Scene/Scene.hpp>

class Application final : public Engine {
public:
    Scene scene;

    // Called just after engine initialization
    void onCreate() override {
        // Create a game object
        GameObject* triangle = scene.createGameObject("Triangle");
        // Connect a MeshRendererComponent to created object, which will render on every update
        auto* meshRendererComponent = triangle->addComponent<MeshRendererComponent>();

        // Create a mesh with 3 position vertices and 3 indices
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
        
        // Create a shader program
        meshRendererComponent->shader.create("resources/shaders/position.vert", "resources/shaders/position.frag");

        // Start all game objects added to scene
        scene.startAllGameObjects();

        // Set window clear color (RGBA)
        setWindowClearColor(0.2f, 0.3f, 0.3f, 1.f);
    }

    // Called every frame between clearing and updating
    void onUpdate() override {
        // Update all objects added to the scene
        scene.updateAllGameObjects();
    }

    // Called just before engine destruction
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
```

## Build Instructions
Because the engine is still developed, there is not a build target available for a static or dynamic library.
However, at the moment the project contains a main file which can be freely modified and your whole project can be built
using attached CMakeLists.txt:
```bash
mkdir build && cd build
cmake ..
make
./Quack
```

## Current goals
- 3D camera
- pre-defined meshes
- Entity Component System
- transforms
- materials

## Future improvements
- Documentation
- Error handling
- Logger
- Time scaling
- Fixed timestep
- Mouse inputs
- Action mapping
- Mouse delta
- Gamepad support
