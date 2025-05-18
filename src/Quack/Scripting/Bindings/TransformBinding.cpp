#include "Quack/Scripting/Bindings/TransformBinding.hpp"
#include "Quack/Scene/Transform.hpp"

void TransformBinding::registerLua(sol::state& lua) {
    lua.new_usertype<Transform>("Transform",
        sol::constructors<Transform()>(),
        "position", &Transform::position,
        "rotation", &Transform::rotation,
        "scale", &Transform::scale
    );
}
