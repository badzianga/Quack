#ifndef QUACK_SCRIPT_COMPONENT_HPP
#define QUACK_SCRIPT_COMPONENT_HPP
#include "Quack/Scene/Component.hpp"
#include <sol/sol.hpp>
#include <string>

class ScriptComponent : public Component {
public:
    void start() override;
    void update() override;

    void loadScript(const std::string& scriptPath);
private:
    sol::state m_lua;
    sol::function m_onStart;
    sol::function m_onUpdate;
};

#endif //QUACK_SCRIPT_COMPONENT_HPP
