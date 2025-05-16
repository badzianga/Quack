#ifndef QUACK_VECTOR_2_BINDING_HPP
#define QUACK_VECTOR_2_BINDING_HPP
#include "Quack/Scripting/ILuaBindable.hpp"
#include "Quack/Math/Vector2.hpp"

class Vector2Binding final : public ILuaBindable {
public:
    void registerLua(sol::state& lua) override {
        lua.new_usertype<Vector2>("Vector2",
            sol::constructors<Vector2(), Vector2(float), Vector2(float, float)>(),

            "x", &Vector2::x,
            "y", &Vector2::y,

            "directionTo", &Vector2::directionTo,
            "distanceTo", &Vector2::distanceTo,
            "distanceToSquared", &Vector2::distanceToSquared,
            "length", &Vector2::length,
            "lengthSquared", &Vector2::lengthSquared,
            "normalized", &Vector2::normalized,

            sol::meta_function::index, [](Vector2& v, int idx) -> float& {
                if (idx == 0) return v.x;
                if (idx == 1) return v.y;
                throw std::out_of_range("Vector2 index out of range (0 or 1)");
            },
            sol::meta_function::new_index, [](Vector2& v, int idx, float value) {
                if (idx == 0) v.x = value;
                else if (idx == 1) v.y = value;
                else throw std::out_of_range("Vector2 index out of range (0 or 1)");
            }
        );

        auto type = lua["Vector2"];

        type[sol::meta_function::addition] = [](const Vector2& v1, const Vector2& v2) -> Vector2 {
            return v1 + v2;
        };
        type[sol::meta_function::subtraction] = [](const Vector2& v1, const Vector2& v2) -> Vector2 {
            return v1 - v2;
        };
        type[sol::meta_function::unary_minus] = [](const Vector2& v) -> Vector2 {
            return -v;
        };
        type[sol::meta_function::multiplication] = [](const sol::object& lhs, const sol::object& rhs) -> Vector2 {
            if (lhs.is<Vector2>() && rhs.is<float>()) {
                return lhs.as<Vector2>() * rhs.as<float>();
            }
            if (lhs.is<float>() && rhs.is<Vector2>()) {
                return lhs.as<float>() * rhs.as<Vector2>();
            }
            throw std::runtime_error("Invalid operands for Vector2 multiplication");
        };
        type[sol::meta_function::division] = [](const Vector2& v, float s) -> Vector2 {
            return v / s;
        };

        lua["Vector2"]["Zero"] = Vector2::Zero;
        lua["Vector2"]["One"] = Vector2::One;
        lua["Vector2"]["Up"] = Vector2::Up;
        lua["Vector2"]["Down"] = Vector2::Down;
        lua["Vector2"]["Left"] = Vector2::Left;
        lua["Vector2"]["Right"] = Vector2::Right;
        lua["Vector2"]["Inf"] = Vector2::Inf;
    }
};

#endif //QUACK_VECTOR_2_BINDING_HPP
