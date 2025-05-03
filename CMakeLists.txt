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

FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 1.0.1)
FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_MakeAvailable(glm)
endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/src/Quack/*/*.cpp"
        "${CMAKE_SOURCE_DIR}/include/Quack/*/*.hpp"
        main.cpp
)

add_executable(Quack ${SRC_FILES})

target_include_directories(Quack PRIVATE include external)
target_link_libraries(Quack PRIVATE libglew_static glfw glm)

file(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")
