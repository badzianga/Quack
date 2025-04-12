cmake_minimum_required(VERSION 3.26)
project(Quack)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git)
FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_MakeAvailable(glad)
    set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
    set(GLAD_API "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
endif()

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw GIT_TAG 3.4)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_MakeAvailable(glfw)
    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
endif()

FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 1.0.1)
FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_MakeAvailable(glm)
endif()

add_executable(Quack main.cpp
        src/Quack/Core/Engine.cpp
        include/Quack/Core/Engine.hpp
        src/Quack/Core/Window.cpp
        include/Quack/Core/Window.hpp
        src/Quack/Core/Time.cpp
        include/Quack/Core/Time.hpp
        src/Quack/Core/Input.cpp
        include/Quack/Core/Input.hpp
        include/Quack/Core/Keyboard.hpp
        src/Quack/Graphics/Shader.cpp
        include/Quack/Graphics/Shader.hpp
        src/Quack/Utils/FileIO.cpp
        include/Quack/Utils/FileIO.hpp
        src/Quack/Graphics/Mesh.cpp
        include/Quack/Graphics/Mesh.hpp
        include/Quack/Graphics/Vertex.hpp
        include/Quack/Core.hpp
        include/Quack/Graphics.hpp
        include/Quack/Utils/LogLevel.hpp
        src/Quack/Utils/Logger.cpp
        include/Quack/Utils/Logger.hpp
        include/Quack/Scene/TransformComponent.hpp
        include/Quack/Scene/GameObject.hpp
        include/Quack/Scene/Component.hpp
        include/Quack/Scene/Scene.hpp
        include/Quack/Scene/MeshRendererComponent.hpp
)

target_include_directories(Quack PRIVATE include)
target_link_libraries(Quack PRIVATE glad glfw glm)

file(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")
