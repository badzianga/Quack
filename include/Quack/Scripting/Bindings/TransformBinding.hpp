#ifndef QUACK_TRANSFORM_BINDING_HPP
#define QUACK_TRANSFORM_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"
#include "Quack/Scene/Transform.hpp"

class TransformBinding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override {
        lua.new_usertype<Transform>("Transform",
            sol::constructors<Transform()>(),
            "position", &Transform::position,
            "rotation", &Transform::rotation,
            "scale", &Transform::scale
        );
    }
};

#endif //QUACK_TRANSFORM_BINDING_HPP
