#include "Quack/Math/Vector3.hpp"
#include "Quack/Math/Vector2.hpp"
#include <cassert>
#include <cmath>

Vector3::Vector3() : x(0.f), y(0.f), z(0.f) {}

Vector3::Vector3(float scalar) : x(scalar), y(scalar), z(scalar) {}

Vector3::Vector3(Vector2 v, float z) : x(v.x), y(v.y), z(z) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float& Vector3::operator[](size_t index) {
    assert(index < 3 && "Index out of bounds");
    return *(&x + index);
}

const float& Vector3::operator[](size_t index) const {
    assert(index < 3 && "Index out of bounds");
    return *(&x + index);
}

Vector3 Vector3::directionTo(const Vector3& to) const {
    return (to - *this).normalized();
}

float Vector3::distanceTo(const Vector3& to) const {
    float dx = to.x - x;
    float dy = to.y - y;
    float dz = to.z - z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

float Vector3::distanceToSquared(const Vector3& to) const {
    float dx = to.x - x;
    float dy = to.y - y;
    float dz = to.z - z;
    return dx * dx + dy * dy + dz * dz;
}

float Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3::lengthSquared() const {
    return x * x + y * y + z * z;
}

Vector3 Vector3::normalized() const {
    return *this / length();
}

float Vector3::dot(const Vector3& left, const Vector3& right) {
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector3 Vector3::cross(const Vector3& left, const Vector3& right) {
    return {
        left.y * right.z - left.z * right.y,
        left.z * right.x - left.x * right.z,
        left.x * right.y - left.y * right.x
    };
}

Vector3 operator+(const Vector3& v1, const Vector3& v2) {
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

Vector3 operator-(const Vector3& v1, const Vector3& v2) {
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

Vector3 operator-(const Vector3& v) {
    return { -v.x, -v.y, -v.z };
}

Vector3 operator*(float scalar, const Vector3& v) {
    return { v.x * scalar, v.y * scalar, v.z * scalar };
}

Vector3 operator*(const Vector3& v, float scalar) {
    return { v.x * scalar, v.y * scalar, v.z * scalar };
}

Vector3 operator/(const Vector3& v, float scalar) {
    return { v.x / scalar, v.y / scalar, v.z / scalar };
}

Vector3& operator+=(Vector3& v1, const Vector3& v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

Vector3& operator-=(Vector3& v1, const Vector3& v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

Vector3& operator*=(Vector3& v, float scalar) {
    v.x *= scalar;
    v.y *= scalar;
    v.z *= scalar;
    return v;
}

Vector3& operator/=(Vector3& v, float scalar) {
    v.x /= scalar;
    v.y /= scalar;
    v.z /= scalar;
    return v;
}

const Vector3 Vector3::Zero{ 0.f };
const Vector3 Vector3::One{ 1.f };
const Vector3 Vector3::Inf{ INFINITY, INFINITY, INFINITY };
const Vector3 Vector3::Left{ -1.f, 0.f, 0.f };
const Vector3 Vector3::Right{ 1.f, 0.f, 0.f };
const Vector3 Vector3::Up{ 0.f, 1.f, 0.f };
const Vector3 Vector3::Down{ 0.f, -1.f, 0.f };
const Vector3 Vector3::Forward{ 0.f, 0.f, -1.f };
const Vector3 Vector3::Back{ 0.f, 0.f, 1.f };
