#ifndef QUACK_SCRIPT_COMPONENT_HPP
#define QUACK_SCRIPT_COMPONENT_HPP
#include "Quack/Scene/Component.hpp"
#include <sol/sol.hpp>
#include <string>

class ScriptComponent final : public Component {
public:
    void start() override;
    void update() override;

    nlohmann::json serialize() override;
    void deserialize(const nlohmann::json& json) override;

    std::string scriptPath;
private:
    void loadScript();

    sol::state m_lua;
    sol::function m_onStart;
    sol::function m_onUpdate;
};

#endif //QUACK_SCRIPT_COMPONENT_HPP
