#ifndef QUACK_MOUSE_BINDING_HPP
#define QUACK_MOUSE_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"
#include "Quack/Core/Mouse.hpp"

class MouseBinding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override {
        lua["MouseButton"] = lua.create_table_with(
            "Left",   Mouse::Button::Left,
            "Right",  Mouse::Button::Right,
            "Middle", Mouse::Button::Middle
        );
    }
};

#endif //QUACK_MOUSE_BINDING_HPP
