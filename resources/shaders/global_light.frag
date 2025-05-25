#version 330 core

in vec2 textureCoord;
in vec3 normal;
in vec3 fragmentPosition;

out vec4 FragColor;

uniform vec4 u_baseColor;
uniform sampler2D u_baseMap;
uniform bool u_hasBaseMap;

uniform vec4 u_lightColor;
uniform float u_ambientIntensity;
uniform vec3 u_lightDirection;
uniform vec3 u_viewPosition;

void main() {
    vec4 textureColor = texture(u_baseMap, textureCoord);
    float useTexture = float(u_hasBaseMap);
    vec4 objectColor = u_baseColor * (useTexture * textureColor + (1.f - useTexture));

    vec4 ambient = u_ambientIntensity * u_lightColor * objectColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-u_lightDirection);
    float diff = max(dot(norm, lightDir), 0.f);
    vec4 diffuse = diff * u_lightColor;

    float specularStrength = 0.5f;
    vec3 viewDirection = normalize(u_viewPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.f), 32);
    vec4 specular = specularStrength * spec * u_lightColor;

    vec4 result = min(ambient + diffuse + specular, 1.f) * objectColor;

    FragColor = result;
}
