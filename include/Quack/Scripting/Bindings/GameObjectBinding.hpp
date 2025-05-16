#ifndef QUACK_GAME_OBJECT_BINDING_HPP
#define QUACK_GAME_OBJECT_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"
#include "Quack/Scene/GameObject.hpp"

class GameObjectBinding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override {
        lua.new_usertype<GameObject>("GameObject",
            "active", &GameObject::active,
            "transform", &GameObject::transform,
            "name", &GameObject::name,
            "parent", &GameObject::parent
        );
    }
};

#endif //QUACK_GAME_OBJECT_BINDING_HPP
