#ifndef QUACK_I_LUA_BINDABLE_HPP
#define QUACK_I_LUA_BINDABLE_HPP
#include <sol/sol.hpp>

class ILuaBindable {
public:
    virtual ~ILuaBindable() = default;

    virtual void registerLua(sol::state& lua) = 0;
};

#endif //QUACK_I_LUA_BINDABLE_HPP
