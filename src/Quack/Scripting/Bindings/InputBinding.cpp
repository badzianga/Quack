#include "Quack/Scripting/Bindings/InputBinding.hpp"
#include "Quack/Core/Input.hpp"

void InputBinding::registerLua(sol::state& lua) {
    lua["Input"] = lua.create_table_with(
        "isKeyPressed", &Input::isKeyPressed,
        "isKeyReleased", &Input::isKeyReleased,
        "isKeyDown", &Input::isKeyDown,
        "isButtonPressed", &Input::isButtonPressed,
        "getMousePosition", &Input::getMousePosition
    );
}
