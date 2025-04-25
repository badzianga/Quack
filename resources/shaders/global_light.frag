#version 330 core

in vec2 textureCoord;

out vec4 FragColor;

uniform vec4 u_baseColor;
uniform sampler2D u_baseMap;
uniform bool u_hasBaseMap;

uniform vec4 u_lightColor;
uniform float u_ambientIntensity;

void main() {
    vec4 textureColor = texture(u_baseMap, textureCoord);
    float useTexture = float(u_hasBaseMap);
    vec4 objectColor = u_baseColor * (useTexture * textureColor + (1.f - useTexture));

    vec4 ambient = u_ambientIntensity * u_lightColor;


    vec4 result = ambient * objectColor;

    FragColor = result;
}
