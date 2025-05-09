#include "Quack/Core/Time.hpp"
#include "Quack/Math/Vector3.hpp"
#include "Quack/Scene/GameObject.hpp"
#include "Quack/Scene/ScriptComponent.hpp"
#include "Quack/Scene/Transform.hpp"
#include "Quack/Utils/Logger.hpp"

void ScriptComponent::start() {
    loadScript();

    if (m_onStart.valid()) {
        m_onStart();
    }
}

void ScriptComponent::update() {
    if (m_onUpdate.valid()) {
        m_onUpdate(Time::getDeltaTime());
    }
}

void ScriptComponent::loadScript() {
    m_lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);

    sol::load_result script = m_lua.load_file(scriptPath);
    if (!script.valid()) {
        sol::error err = script;
        Logger::error("Script error: " + std::string(err.what()));
        return;
    }

    m_lua.new_usertype<Vector3>("Vector3",
        sol::constructors<Vector3()>(),
        "x", &Vector3::x,
        "y", &Vector3::y,
        "z", &Vector3::z
    );

    m_lua.new_usertype<Transform>("Transform",
        sol::constructors<Transform()>(),
        "position", &Transform::position,
        "rotation", &Transform::rotation,
        "scale", &Transform::scale
    );

    m_lua.new_usertype<GameObject>("GameObject",
        "transform", &GameObject::transform
    );

    script();

    m_onStart = m_lua["onStart"];
    m_onUpdate = m_lua["onUpdate"];
    m_lua["gameObject"] = gameObject;
}
