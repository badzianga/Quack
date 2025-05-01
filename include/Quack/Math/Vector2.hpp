#ifndef QUACK_VECTOR_2_HPP
#define QUACK_VECTOR_2_HPP
#include <cstddef>

class Vector2 {
public:
    Vector2();
    Vector2(float scalar);
    Vector2(float x, float y);

    float& operator[](size_t index);
    const float& operator[](size_t index) const;

    [[nodiscard]] Vector2 directionTo(const Vector2& to) const;
    [[nodiscard]] float distanceTo(const Vector2& to) const;
    [[nodiscard]] float distanceToSquared(const Vector2& to) const;
    [[nodiscard]] float length() const;
    [[nodiscard]] float lengthSquared() const;
    [[nodiscard]] Vector2 normalized() const;

    static const Vector2 Zero;
    static const Vector2 One;
    static const Vector2 Inf;
    static const Vector2 Left;
    static const Vector2 Right;
    static const Vector2 Up;
    static const Vector2 Down;

    float x, y;
};

Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v);
Vector2 operator*(float scalar, const Vector2& v);
Vector2 operator*(const Vector2& v, float scalar);
Vector2 operator/(const Vector2& v, float scalar);
Vector2& operator+=(Vector2& v1, const Vector2& v2);
Vector2& operator-=(Vector2& v1, const Vector2& v2);
Vector2& operator*=(Vector2& v, float scalar);
Vector2& operator/=(Vector2& v, float scalar);

#endif //QUACK_VECTOR_2_HPP
