#include "Quack/Core/Time.hpp"
#include "Quack/Scene/ScriptComponent.hpp"
#include "Quack/Utils/Logger.hpp"


void ScriptComponent::start() {
    if (m_onStart.valid()) {
        m_onStart();
    }
}

void ScriptComponent::update() {
    if (m_onUpdate.valid()) {
        m_onUpdate(Time::getDeltaTime());
    }
}

void ScriptComponent::loadScript(const std::string& scriptPath) {
    m_lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);

    sol::load_result script = m_lua.load_file(scriptPath);
    if (!script.valid()) {
        sol::error err = script;
        Logger::error("Script error: " + std::string(err.what()));
        return;
    }

    script();

    m_onStart = m_lua["onStart"];
    m_onUpdate = m_lua["onUpdate"];
}
