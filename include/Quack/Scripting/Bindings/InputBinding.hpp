#ifndef QUACK_INPUT_BINDING_HPP
#define QUACK_INPUT_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"

class InputBinding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override;
};

#endif //QUACK_INPUT_BINDING_HPP
