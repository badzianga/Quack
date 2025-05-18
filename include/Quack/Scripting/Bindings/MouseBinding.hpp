#ifndef QUACK_MOUSE_BINDING_HPP
#define QUACK_MOUSE_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"

class MouseBinding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override;
};

#endif //QUACK_MOUSE_BINDING_HPP
