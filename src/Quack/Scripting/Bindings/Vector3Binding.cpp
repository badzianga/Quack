#include "Quack/Scripting/Bindings/Vector3Binding.hpp"
#include "Quack/Math/Vector2.hpp"
#include "Quack/Math/Vector3.hpp"

void Vector3Binding::registerLua(sol::state& lua) {
    lua.new_usertype<Vector3>("Vector3",
        sol::constructors<Vector3(), Vector3(float), Vector3(Vector2, float), Vector3(float, float, float)>(),

        "x", &Vector3::x,
        "y", &Vector3::y,
        "z", &Vector3::z,

        "directionTo", &Vector3::directionTo,
        "distanceTo", &Vector3::distanceTo,
        "distanceToSquared", &Vector3::distanceToSquared,
        "length", &Vector3::length,
        "lengthSquared", &Vector3::lengthSquared,
        "normalized", &Vector3::normalized,

        sol::meta_function::index, [](Vector3& v, int idx) -> float& {
            if (idx == 0) return v.x;
            if (idx == 1) return v.y;
            if (idx == 2) return v.z;
            throw std::out_of_range("Vector3 index out of range (0 or 1)");
        },
        sol::meta_function::new_index, [](Vector3& v, int idx, float value) {
            if (idx == 0) v.x = value;
            else if (idx == 1) v.y = value;
            else if (idx == 2) v.z = value;
            else throw std::out_of_range("Vector3 index out of range (0 or 1)");
        }
    );

    auto type = lua["Vector3"];

    type[sol::meta_function::addition] = [](const Vector3& v1, const Vector3& v2) -> Vector3 {
        return v1 + v2;
    };
    type[sol::meta_function::subtraction] = [](const Vector3& v1, const Vector3& v2) -> Vector3 {
        return v1 - v2;
    };
    type[sol::meta_function::unary_minus] = [](const Vector3& v) -> Vector3 {
        return -v;
    };
    type[sol::meta_function::multiplication] = [](const sol::object& lhs, const sol::object& rhs) -> Vector3 {
        if (lhs.is<Vector3>() && rhs.is<float>()) {
            return lhs.as<Vector3>() * rhs.as<float>();
        }
        if (lhs.is<float>() && rhs.is<Vector3>()) {
            return lhs.as<float>() * rhs.as<Vector3>();
        }
        throw std::runtime_error("Invalid operands for Vector3 multiplication");
    };
    type[sol::meta_function::division] = [](const Vector3& v, float s) -> Vector3 {
        return v / s;
    };

    lua["Vector3"]["Zero"] = Vector3::Zero;
    lua["Vector3"]["One"] = Vector3::One;
    lua["Vector3"]["Up"] = Vector3::Up;
    lua["Vector3"]["Down"] = Vector3::Down;
    lua["Vector3"]["Left"] = Vector3::Left;
    lua["Vector3"]["Right"] = Vector3::Right;
    lua["Vector3"]["Inf"] = Vector3::Inf;
}
