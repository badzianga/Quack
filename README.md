# Quack Engine

Quack Engine is a currently developed small 3D game engine created using C++ and OpenGL.

## Usage Example
```C++
#include <Quack/Core/Engine.hpp>
#include <Quack/Core/Time.hpp>
#include <Quack/Scene/CameraComponent.hpp>
#include <Quack/Scene/MeshRendererComponent.hpp>
#include <Quack/Scene/Scene.hpp>

class Application final : public Engine {
public:
    Scene scene;
    GameObject* myCube = nullptr;

    // Called just after engine initialization
    void onCreate() override {
        // Create a game object and attach CameraComponent to it
        GameObject* camera = scene.createGameObject("Camera");
        camera->addComponent<CameraComponent>();
    
        // Create another game object
        myCube = scene.createGameObject("MyCube");
        
        // Connect a MeshRendererComponent to created object, which will render on every update
        auto* meshRendererComponent = myCube->addComponent<MeshRendererComponent>();

        // Create a cube mesh
        meshRendererComponent->mesh = Mesh::createCube();

        // Set position of the cube object using its TransformComponent
        myCube->getComponent<TransformComponent>()->position = glm::vec3(0, 0, -2);
        
        // Create a shader program in the MeshRenderer object
        meshRendererComponent->shader.create("resources/shaders/universal.vert", "resources/shaders/universal.frag");

        // Start all game objects added to scene
        scene.startAllGameObjects();

        // Set window clear color (RGBA)
        setWindowClearColor(0.2f, 0.3f, 0.3f, 1.f);
    }

    // Called every frame between clearing and updating
    void onUpdate() override {
        // Rotate the cube 60 degrees per second
        myCube->getComponent<TransformComponent>()->rotation.y += 60.f * Time::getDeltaTime();
    
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
- materials

## Future improvements
- Documentation
- Time scaling
- Fixed timestep
- Mouse inputs
- Action mapping
- Mouse delta
- Gamepad support
