#include "Quack/Scripting/Bindings/GameObjectBinding.hpp"
#include "Quack/Scene/GameObject.hpp"

void GameObjectBinding::registerLua(sol::state& lua) {
    lua.new_usertype<GameObject>("GameObject",
        "active", &GameObject::active,
        "transform", &GameObject::transform,
        "name", &GameObject::name,
        "parent", &GameObject::parent
    );
}