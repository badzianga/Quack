#version 330 core

out vec4 FragColor;

uniform vec4 u_colorMap;

void main() {
    FragColor = u_colorMap;
}
