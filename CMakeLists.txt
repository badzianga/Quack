cmake_minimum_required(VERSION 3.26)
project(Quack)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        GIT_TAG        master
        SOURCE_DIR     ${CMAKE_BINARY_DIR}/_deps/glew-src
        BINARY_DIR     ${CMAKE_BINARY_DIR}/_deps/glew-build
)
FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
    FetchContent_MakeAvailable(glew)
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

FetchContent_Declare(lua GIT_REPOSITORY https://github.com/lua/lua.git GIT_TAG v5.4.7)
FetchContent_GetProperties(lua)
if (NOT lua_POPULATED)
    FetchContent_MakeAvailable(lua)
endif()

FetchContent_Declare(sol2 GIT_REPOSITORY https://github.com/ThePhD/sol2.git GIT_TAG v3.5.0)
FetchContent_GetProperties(sol2)
if (NOT sol2_POPULATED)
    FetchContent_MakeAvailable(sol2)
endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/src/Quack/*/*.cpp"
        "${CMAKE_SOURCE_DIR}/include/Quack/*/*.hpp"
        "${CMAKE_SOURCE_DIR}/include/Quack/*/*.inl"
        "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

add_library(Quack STATIC ${SRC_FILES})

target_include_directories(Quack PUBLIC include external)
target_link_libraries(Quack PUBLIC libglew_static glfw lua sol2)

file(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")



add_executable(QuackSandbox main.cpp)
target_link_libraries(QuackSandbox PRIVATE Quack)



FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG docking
)
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_MakeAvailable(imgui)
endif()

find_package(OpenGL REQUIRED)

add_library(imgui_lib
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
)

target_include_directories(imgui_lib PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${imgui_SOURCE_DIR}/misc/cpp
)

target_link_libraries(imgui_lib PRIVATE glfw OpenGL::GL)

add_executable(QuackEditor editor/editor.cpp
        editor/src/ImGuiConfig.cpp
        editor/include/ImGuiConfig.hpp
)

target_include_directories(QuackEditor PRIVATE
        editor/include
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(QuackEditor PUBLIC glfw imgui_lib Quack)

configure_file(imgui.ini ${CMAKE_BINARY_DIR}/imgui.ini COPYONLY)
