#ifndef QUACK_KEYBOARD_BINDING_HPP
#define QUACK_KEYBOARD_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"

class KeyboardBinding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override;
};

#endif //QUACK_KEYBOARD_BINDING_HPP
