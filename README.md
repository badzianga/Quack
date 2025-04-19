# Quack Engine

Quack Engine is a currently developed small 3D game engine created using C++ and OpenGL.

## Features
Since Quack Engine is still in development, it doesn't have many features. However, for now, it allows you to:
- create your own Engine-derived class with auto-called methods
- create a scene with objects to which you can connect components
- render pre-defined meshes (plane, cube)
- transform objects on the scene

## Usage Example
Code below shows a small example how to use the engine. Simple, work-in-progress documentation with described classes
is available [here](https://quackengine.netlify.app/annotated.html).
```C++
#include <Quack/Core/Engine.hpp>
#include <Quack/Core/Time.hpp>
#include <Quack/Graphics/Mesh.hpp>
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

        // Set position of the cube object using its TransformComponent
        myCube->getComponent<TransformComponent>()->position = glm::vec3(0, 0, -2);
        
        // Connect a MeshRendererComponent to created object, which will render on every update
        auto* meshRendererComponent = myCube->addComponent<MeshRendererComponent>();

        // Add a cube mesh to the MeshRenderer object
        meshRendererComponent->mesh = Mesh::createCube(); 

        // Create a shader program in the MeshRenderer object
        meshRendererComponent->shader.create("resources/shaders/universal.vert", "resources/shaders/universal.frag");

        // Set the blue color of the created object
        meshRendererComponent->material.baseColor = Color::Blue;

        // Start all game objects added to scene
        scene.startAllGameObjects();

        // Set window clear color (RGBA)
        accessWindow().setClearColor({0.2f, 0.3f, 0.3f, 1.f});
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

    if (app.create(1024, 768, "Quack Engine Example")) {
        app.start();
    }

    app.destroy();

    return 0;
}
```

## Build Instructions
Because the engine is still developed, there is not a build target available for a static or dynamic library.
However, at the moment the project contains a main file which can be freely modified and your whole project can be built
using attached CMakeLists.txt.

### Windows
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Linux
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## Future improvements and features
- 3D light
- Mesh/Shader/Texture manager with one instance of objects, references to them in components
- Pre-defined shaders
- Matrix and Vector classes
- ScriptComponent and scripting
- Interactive editor
- RigidBodyComponent with basic physics
- Capsule and sphere meshes
- Time scaling
- Fixed timestep
- Action mapping
- Mouse delta
- Gamepad support
