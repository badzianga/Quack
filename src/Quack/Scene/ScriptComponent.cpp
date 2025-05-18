#include "Quack/Core/Time.hpp"
#include "Quack/Bindings.hpp"
#include "Quack/Scene/ScriptComponent.hpp"
#include "Quack/Scene/GameObject.hpp"
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

    Vector2Binding v2Binding;
    v2Binding.registerLua(m_lua);

    Vector3Binding v3Binding;
    v3Binding.registerLua(m_lua);

    TransformBinding tBinding;
    tBinding.registerLua(m_lua);

    GameObjectBinding goBinding;
    goBinding.registerLua(m_lua);

    MouseBinding mBinding;
    mBinding.registerLua(m_lua);

    KeyboardBinding kBinding;
    kBinding.registerLua(m_lua);

    InputBinding iBinding;
    iBinding.registerLua(m_lua);

    sol::protected_function_result result = script();
    if (!result.valid()) {
        sol::error err = result;
        Logger::error("Script error: " + std::string(err.what()));
        return;
    }

    m_onStart = m_lua["onStart"];
    m_onUpdate = m_lua["onUpdate"];
    m_lua["gameObject"] = gameObject;
}
