#ifndef QUACK_TRANSFORM_BINDING_HPP
#define QUACK_TRANSFORM_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"

class TransformBinding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override;
};

#endif //QUACK_TRANSFORM_BINDING_HPP
