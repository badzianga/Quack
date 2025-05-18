#ifndef QUACK_GAME_OBJECT_BINDING_HPP
#define QUACK_GAME_OBJECT_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"

class GameObjectBinding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override;
};

#endif //QUACK_GAME_OBJECT_BINDING_HPP
