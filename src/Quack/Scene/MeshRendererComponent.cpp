#include "Quack/Graphics/GlobalLight.hpp"
#include "Quack/Math/Matrix3.hpp"
#include "Quack/Scene/CameraComponent.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/MeshRendererComponent.hpp"
#include <nlohmann/json.hpp>

// TODO: mesh and shader are not destroyed, even after closing window

void MeshRendererComponent::start() {}

void MeshRendererComponent::update() {
    if (!enabled) return;

    Matrix4 model;
    if (gameObject->parent) {
        model = getModelMatrix(gameObject->parent->transform) * getModelMatrix(gameObject->transform);
    }
    else {
        model = getModelMatrix(gameObject->transform);
    }
    Matrix4 mvp = CameraComponent::getStaticProjectionView() * model;

    shader.use();
    shader.set("u_mvp", mvp);
    shader.set("u_baseColor", material.baseColor);
    if (material.baseMap != nullptr) {
        shader.set("u_hasBaseMap", true);
        material.baseMap->bind();
    }
    else {
        shader.set("u_hasBaseMap", false);
    }

    // Set lights even if the current shader doesn't support it
    shader.set("u_lightColor", GlobalLight::color);
    shader.set("u_ambientIntensity", GlobalLight::ambientIntensity);
    shader.set("u_lightDirection", GlobalLight::direction);
    Matrix3 normalMatrix = Matrix3(model).inversed().transposed();
    shader.set("u_normalMatrix", normalMatrix);

    mesh.draw();

    // TODO: consider unbinding texture
}

Matrix4 MeshRendererComponent::getModelMatrix(const Transform& transform) {
    Matrix4 model = Matrix4::Identity;

    model.translate(transform.position);
    model.rotate(Math::toRadians(transform.rotation.x), { 1.f, 0.f, 0.f });
    model.rotate(Math::toRadians(transform.rotation.y), { 0.f, 1.f, 0.f });
    model.rotate(Math::toRadians(transform.rotation.z), { 0.f, 0.f, 1.f });
    model.scale(transform.scale);

    return model;
}

nlohmann::json MeshRendererComponent::serialize() {
    nlohmann::json json;

    json["componentType"] = "MeshRenderer";
    json["enabled"] = enabled;
    // TODO: serialize which model and shader is used (ModelManager and ShaderManager will be needed I think)
    // TODO: material should be IJsonSerializable
    json["material"] = nlohmann::json::object();
    json["material"]["baseColor"] = nlohmann::json::array({ material.baseColor.r, material.baseColor.g, material.baseColor.b, material.baseColor.a });

    return json;
}

void MeshRendererComponent::deserialize(const nlohmann::json& json) {
    enabled = json["enabled"];
    // TODO: model and shader are not serialized, so always use Cube model and global_light shader
    mesh = Mesh::createCube();
    shader.create("resources/shaders/global_light.vert", "resources/shaders/global_light.frag");

    // TODO: material should be IJsonSerializable
    material.baseColor.r = json["material"]["baseColor"][0];
    material.baseColor.g = json["material"]["baseColor"][1];
    material.baseColor.b = json["material"]["baseColor"][2];
    material.baseColor.a = json["material"]["baseColor"][3];
}
