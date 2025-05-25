#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_textureCoord;

out vec2 textureCoord;
out vec3 normal;
out vec3 fragmentPosition;

uniform mat4 u_mvp;
uniform mat3 u_normalMatrix;
uniform mat4 u_modelMatrix;

void main() {
    gl_Position = u_mvp * vec4(a_position, 1.f);
    textureCoord = a_textureCoord;
    normal = u_normalMatrix * a_normal;
    fragmentPosition = vec3(u_modelMatrix * vec4(a_position, 1.f));
}
