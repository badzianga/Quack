#include "Quack/Graphics/Shader.hpp"
#include "Quack/Utils/FileIO.hpp"
#include <glad/glad.h>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader() : m_id(0) {}

bool Shader::create(const char* vertexPath, const char* fragmentPath) {
    m_id = glCreateProgram();

    std::string vertexShaderString = FileIO::read(vertexPath);
    const char* vertexShaderSource = vertexShaderString.c_str();
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    std::string fragmentShaderString = FileIO::read(fragmentPath);
    const char* fragmentShaderSource = fragmentShaderString.c_str();
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

bool Shader::destroy() {
    glDeleteProgram(m_id);
    m_id = 0;

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

int32_t Shader::getUniformLocation(const char *name) {
    auto locationIterator = m_uniformLocationCache.find(name);
    if (locationIterator != m_uniformLocationCache.end()) {
        return locationIterator->second;
    }
    int32_t location = glGetUniformLocation(m_id, name);
    m_uniformLocationCache[name] = location;
    return location;
}
