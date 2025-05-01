#include "Quack/Math/Vector2.hpp"
#include <cassert>
#include <cmath>

Vector2::Vector2() : x(0.f), y(0.f) {}

Vector2::Vector2(float scalar) : x(scalar), y(scalar) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float& Vector2::operator[](size_t index) {
    assert(index < 2 && "Index out of bounds");
    return *(&x + index);
}

const float& Vector2::operator[](size_t index) const {
    assert(index < 2 && "Index out of bounds");
    return *(&x + index);
}

Vector2 Vector2::directionTo(const Vector2& to) const {
    return (to - *this).normalized();
}

float Vector2::distanceTo(const Vector2& to) const {
    float dx = to.x - x;
    float dy = to.y - y;
    return std::sqrt(dx * dx + dy * dy);
}

float Vector2::distanceToSquared(const Vector2& to) const {
    float dx = to.x - x;
    float dy = to.y - y;
    return dx * dx + dy * dy;
}

float Vector2::length() const {
    return std::sqrt(x * x + y * y);
}

float Vector2::lengthSquared() const {
    return x * x + y * y;
}

Vector2 Vector2::normalized() const {
    return *this / length();
}

Vector2 operator+(const Vector2& v1, const Vector2& v2) {
    return { v1.x + v2.x, v1.y + v2.y };
}

Vector2 operator-(const Vector2& v1, const Vector2& v2) {
    return { v1.x - v2.x, v1.y - v2.y };
}

Vector2 operator-(const Vector2 &v) {
    return { -v.x, -v.y };
}

Vector2 operator*(float scalar, const Vector2& v) {
    return { v.x * scalar, v.y * scalar };
}

Vector2 operator*(const Vector2& v, float scalar) {
    return { v.x * scalar, v.y * scalar };
}

Vector2 operator/(const Vector2& v, float scalar) {
    return { v.x / scalar, v.y / scalar };
}

Vector2& operator+=(Vector2& v1, const Vector2& v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

Vector2& operator-=(Vector2& v1, const Vector2& v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

Vector2& operator*=(Vector2& v, float scalar) {
    v.x *= scalar;
    v.y *= scalar;
    return v;
}

Vector2& operator/=(Vector2& v, float scalar) {
    v.x /= scalar;
    v.y /= scalar;
    return v;
}

const Vector2 Vector2::Zero{ 0.f };
const Vector2 Vector2::One{ 1.f};
const Vector2 Vector2::Inf{ INFINITY, INFINITY };
const Vector2 Vector2::Left{ -1.f, 0.f };
const Vector2 Vector2::Right{ 1.f, 0.f };
const Vector2 Vector2::Up{ 0.f, 1.f };
const Vector2 Vector2::Down{ 0.f, -1.f };