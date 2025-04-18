#ifndef QUACK_SHADER_HPP
#define QUACK_SHADER_HPP
#include "Quack/Graphics/Color.hpp"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <glm/fwd.hpp>

/**
 * @brief Representation of a shader program.
 *
 * This class manages the creation, compilation, and use of a shader program,
 * which is composed of a vertex shader and a fragment shader. It also
 * provides methods to set uniform variables in the shader program.
 */
class Shader {
public:
    /**
     * @brief Default constructor.
     *
     * This constructor doesn't actually create the shader,
     * it is used only to declare the object.
     */
    Shader();

    /**
     * @brief Destructor.
     *
     * Cleans up any resources associated with the shader program, such as
     * deleting the shader program from OpenGL.
     */
    ~Shader();

    /**
     * @brief Deleted copy constructor.
     *
     * Shader objects cannot be copied.
     */
    Shader(const Shader&) = delete;

    /**
     * @brief Move constructor
     *
     * Transfers ownership of shader resources from one Shader to another.
     *
     * @param other The shader to move from.
     */
    Shader(Shader&& other) noexcept;

    /**
     * @brief Deleted copy assignment.
     *
     * Shader objects cannot be copied.
     */
    Shader& operator=(const Shader&) = delete;

    /**
     * @brief Move assignment operator.
     *
     * Transfers ownership of shader resources from one Shader
     * to another using assignment.
     *
     * @param other The shader to move from.
     * @return Reference to the current shader object.
     */
    Shader& operator=(Shader&& other) noexcept;

    /**
     * @brief Create a shader program from vertex and fragment shader files.
     *
     * Loads, compiles, and links the shaders into a complete shader program.
     * This method is called to initialize the shader object.
     *
     * @param vertexPath The file path to the vertex shader.
     * @param fragmentPath The file path to the fragment shader.
     * @return True if the shader program was successfully created, false otherwise.
     */
    bool create(const char* vertexPath, const char* fragmentPath);

    /**
     * @brief Destroy the shader program and free resources.
     *
     * Deletes the shader program and all associated resources from OpenGL.
     *
     * @return True if the shader was successfully destroyed, false otherwise.
     */
    bool destroy();

    /**
     * @brief Activates the shader program for rendering.
     *
     * This method tells OpenGL to use this shader program for subsequent rendering calls.
     */
    void use() const;

    /**
     * @brief Set an integer uniform variable in the shader program.
     *
     * @param name The name of the uniform variable.
     * @param value The integer value to set.
     */
    void set(const char* name, int value);

    /**
     * @brief Set a float uniform variable in the shader program.
     *
     * @param name The name of the uniform variable.
     * @param value The float value to set.
     */
    void set(const char* name, float value);

    /**
     * @brief Set a 2D vector uniform variable in the shader program.
     *
     * @param name The name of the uniform variable.
     * @param value The 2D vector value to set.
     */
    void set(const char* name, const glm::vec2& value);

    /**
     * @brief Set a 3D vector uniform variable in the shader program.
     *
     * @param name The name of the uniform variable.
     * @param value The 3D vector value to set.
     */
    void set(const char* name, const glm::vec3& value);

    /**
     * @brief Set a 4D vector uniform variable in the shader program.
     *
     * @param name The name of the uniform variable.
     * @param value The 4D vector value to set.
     */
    void set(const char* name, const glm::vec4& value);

    /**
     * @brief Set a 2x2 matrix uniform variable in the shader program.
     *
     * @param name The name of the uniform variable.
     * @param value The 2x2 matrix value to set.
     */
    void set(const char* name, const glm::mat2& value);

    /**
     * @brief Set a 3x3 matrix uniform variable in the shader program.
     *
     * @param name The name of the uniform variable.
     * @param value The 3x3 matrix value to set.
     */
    void set(const char* name, const glm::mat3& value);

    /**
     * @brief Set a 4x4 matrix uniform variable in the shader program.
     *
     * @param name The name of the uniform variable.
     * @param value The 4x4 matrix value to set.
     */
    void set(const char* name, const glm::mat4& value);

    /**
     * @brief Set a color uniform variable in the shader program.
     *
     * @param name The name of the uniform variable.
     * @param value The color value to set.
     */
    void set(const char* name, Color value);

private:
    uint32_t m_id;
    std::unordered_map<const char*, int32_t> m_uniformLocationCache;

    /**
     * @brief Retrieve the location of a uniform variable.
     *
     * This method checks the cache for the uniform location. If not found, it queries OpenGL
     * for the location.
     *
     * @param name The name of the uniform variable.
     * @return The location of the uniform variable.
     */
    int32_t getUniformLocation(const char* name);

    /**
     * @brief Check for shader compilation errors.
     *
     * This method checks if the shader compiled successfully and prints any errors.
     *
     * @param shaderID The ID of the shader to check.
     * @param type The type of the shader (vertex or fragment).
     * @return True if the shader compiled successfully, false if there were errors.
     */
    static bool checkCompileErrors(uint32_t shaderID, const std::string& type);

    /**
     * @brief Check for shader program linking errors.
     *
     * This method checks if the shader program linked successfully and prints any errors.
     *
     * @param programID The ID of the shader program to check.
     * @return True if the program linked successfully, false if there were errors.
     */
    static bool checkLinkErrors(uint32_t programID);
};

#endif //QUACK_SHADER_HPP
