#ifndef QUACK_INPUT_BINDING_HPP
#define QUACK_INPUT_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"
#include "Quack/Core/Input.hpp"

class InputBinding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override {
        lua["Input"] = lua.create_table_with(
            "isKeyPressed", &Input::isKeyPressed,
            "isKeyReleased", &Input::isKeyReleased,
            "isKeyDown", &Input::isKeyDown,
            "isButtonPressed", &Input::isButtonPressed,
            "getMousePosition", &Input::getMousePosition
        );
    }
};

#endif //QUACK_INPUT_BINDING_HPP
