#include "Quack/Graphics/Shader.hpp"
#include "Quack/Utils.hpp"
#include <utility>
#include <GL/glew.h>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader() : m_id(0) {}

Shader::~Shader() = default;

Shader::Shader(Shader&& other) noexcept
    : m_id(std::exchange(other.m_id, 0)),
      m_uniformLocationCache(std::move(other.m_uniformLocationCache)) {

    other.m_uniformLocationCache.clear();

    Logger::debug("Shader object moved using constructor");
}

Shader& Shader::operator=(Shader&& other) noexcept {
    m_id = std::exchange(other.m_id, 0);
    m_uniformLocationCache = std::move(other.m_uniformLocationCache);

    other.m_uniformLocationCache.clear();

    Logger::debug("Shader object moved using assignment operator");
    return *this;
}

bool Shader::create(const char* vertexPath, const char* fragmentPath) {
    std::string vertexShaderString = FileIO::read(vertexPath);
    const char* vertexShaderSource = vertexShaderString.c_str();
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    if (checkCompileErrors(vertexShader, "Vertex")) {
        Logger::debug("Vertex shader compiled successfully");
    }

    std::string fragmentShaderString = FileIO::read(fragmentPath);
    const char* fragmentShaderSource = fragmentShaderString.c_str();
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    if (checkCompileErrors(vertexShader, "Fragment")) {
        Logger::debug("Fragment shader compiled successfully");
    }

    m_id = glCreateProgram();

    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);
    if (checkLinkErrors(m_id)) {
        Logger::debug("Shader program linked successfully");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

bool Shader::destroy() {
    glDeleteProgram(m_id);
    m_id = 0;

    Logger::debug("Shader program destroyed");

    return true;
}

void Shader::use() const {
    glUseProgram(m_id);
}

void Shader::set(const char* name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::set(const char* name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::set(const char* name, const glm::vec2& value) {
    glUniform2f(getUniformLocation(name), value.x, value.y);
}

void Shader::set(const char* name, const glm::vec3& value) {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::set(const char* name, const glm::vec4& value) {
    glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::set(const char* name, const glm::mat2& value) {
    glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set(const char* name, const glm::mat3& value) {
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set(const char* name, const glm::mat4& value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set(const char* name, Color value) {
    glUniform4f(getUniformLocation(name), value.r, value.g, value.b, value.a);
}

void Shader::set(const char* name, const Vector2& value) {
    glUniform2f(getUniformLocation(name), value.x, value.y);
}

void Shader::set(const char* name, const Vector3& value) {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::set(const char* name, const Vector4& value) {
    glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);

}

void Shader::set(const char* name, const Matrix4& value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value.get());
}

int32_t Shader::getUniformLocation(const char *name) {
    auto locationIterator = m_uniformLocationCache.find(name);
    if (locationIterator != m_uniformLocationCache.end()) {
        return locationIterator->second;
    }
    int32_t location = glGetUniformLocation(m_id, name);
    m_uniformLocationCache[name] = location;
    return location;
}

bool Shader::checkCompileErrors(uint32_t shaderID, const std::string& type) {
    int success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
        Logger::error(type + " shader compilation error: " + std::string(infoLog));
        return false;
    }
    return true;
}

bool Shader::checkLinkErrors(uint32_t programID) {
    int success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(programID, 1024, nullptr, infoLog);
        Logger::error("Shader program compilation error: " + std::string(infoLog));
        return false;
    }
    return true;
}
