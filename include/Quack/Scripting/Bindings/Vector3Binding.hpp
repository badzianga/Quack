#ifndef QUACK_VECTOR_3_BINDING_HPP
#define QUACK_VECTOR_3_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"

class Vector3Binding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override;
};

#endif //QUACK_VECTOR_3_BINDING_HPP
