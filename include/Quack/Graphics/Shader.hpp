#ifndef QUACK_SHADER_HPP
#define QUACK_SHADER_HPP
#include <cstdint>
#include <string>
#include <unordered_map>
#include <glm/fwd.hpp>

class Shader {
public:
    Shader();
    ~Shader() = default;

    Shader(const Shader&) = delete;
    Shader(Shader&& other) noexcept;
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&& other) noexcept;

    bool create(const char* vertexPath, const char* fragmentPath);
    bool destroy();

    void use() const;
    void set(const char* name, int value);
    void set(const char* name, float value);
    void set(const char* name, const glm::vec2& value);
    void set(const char* name, const glm::vec3& value);
    void set(const char* name, const glm::vec4& value);
    void set(const char* name, const glm::mat2& value);
    void set(const char* name, const glm::mat3& value);
    void set(const char* name, const glm::mat4& value);

private:
    uint32_t m_id;
    std::unordered_map<const char*, int32_t> m_uniformLocationCache;

    int32_t getUniformLocation(const char* name);
    static bool checkCompileErrors(uint32_t shaderID, const std::string& type);
    static bool checkLinkErrors(uint32_t programID);
};

#endif //QUACK_SHADER_HPP
