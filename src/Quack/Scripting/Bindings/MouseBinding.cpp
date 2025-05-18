#include "Quack/Scripting/Bindings/MouseBinding.hpp"
#include "Quack/Core/Mouse.hpp"

void MouseBinding::registerLua(sol::state& lua) {
    lua["MouseButton"] = lua.create_table_with(
        "Left",   Mouse::Button::Left,
        "Right",  Mouse::Button::Right,
        "Middle", Mouse::Button::Middle
    );
}
