#ifndef QUACK_VECTOR_2_BINDING_HPP
#define QUACK_VECTOR_2_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"

class Vector2Binding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override;
};

#endif //QUACK_VECTOR_2_BINDING_HPP
