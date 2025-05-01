#include "Quack/Math/Vector4.hpp"
#include "Quack/Math/Vector2.hpp"
#include "Quack/Math/Vector3.hpp"
#include <cassert>
#include <cmath>

Vector4::Vector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}

Vector4::Vector4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}

Vector4::Vector4(Vector2 v, float z, float w) : x(v.x), y(v.y), z(z), w(w) {}

Vector4::Vector4(Vector3 v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

float& Vector4::operator[](size_t index) {
    assert(index < 4 && "Index out of bounds");
    return *(&x + index);
}

const float& Vector4::operator[](size_t index) const {
    assert(index < 4 && "Index out of bounds");
    return *(&x + index);
}

Vector4 Vector4::directionTo(const Vector4& to) const {
    return (to - *this).normalized();
}

float Vector4::distanceTo(const Vector4& to) const {
    float dx = to.x - x;
    float dy = to.y - y;
    float dz = to.z - z;
    float dw = to.w - w;
    return std::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

float Vector4::distanceToSquared(const Vector4& to) const {
    float dx = to.x - x;
    float dy = to.y - y;
    float dz = to.z - z;
    float dw = to.w - w;
    return dx * dx + dy * dy + dz * dz + dw * dw;
}

float Vector4::length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

float Vector4::lengthSquared() const {
    return x * x + y * y + z * z + w * w;
}

Vector4 Vector4::normalized() const {
    return *this / length();
}

Vector4 operator+(const Vector4& v1, const Vector4& v2) {
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
}

Vector4 operator-(const Vector4& v1, const Vector4& v2) {
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
}

Vector4 operator-(const Vector4& v) {
    return { -v.x, -v.y, -v.z, -v.w };
}

Vector4 operator*(float scalar, const Vector4& v) {
    return { v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar };
}

Vector4 operator*(const Vector4& v, float scalar) {
    return { v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar };
}

Vector4 operator/(const Vector4& v, float scalar) {
    return { v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar };
}

Vector4& operator+=(Vector4& v1, const Vector4& v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    v1.w += v2.w;
    return v1;
}

Vector4& operator-=(Vector4& v1, const Vector4& v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    v1.w -= v2.w;
    return v1;
}

Vector4& operator*=(Vector4& v, float scalar) {
    v.x *= scalar;
    v.y *= scalar;
    v.z *= scalar;
    v.w *= scalar;
    return v;
}

Vector4& operator/=(Vector4& v, float scalar) {
    v.x /= scalar;
    v.y /= scalar;
    v.z /= scalar;
    v.w /= scalar;
    return v;
}

const Vector4 Vector4::Zero{ 0.f };
const Vector4 Vector4::One{ 1.f };
const Vector4 Vector4::Inf{ INFINITY };
