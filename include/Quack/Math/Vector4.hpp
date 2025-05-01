#ifndef QUACK_VECTOR_4_HPP
#define QUACK_VECTOR_4_HPP
#include <cstddef>

class Vector2;
class Vector3;

class Vector4 {
public:
    Vector4();
    Vector4(float scalar);
    Vector4(Vector2 v, float z, float w);
    Vector4(Vector3 v, float w);
    Vector4(float x, float y, float z, float w);

    float& operator[](size_t index);
    const float& operator[](size_t index) const;

    [[nodiscard]] Vector4 directionTo(const Vector4& to) const;
    [[nodiscard]] float distanceTo(const Vector4& to) const;
    [[nodiscard]] float distanceToSquared(const Vector4& to) const;
    [[nodiscard]] float length() const;
    [[nodiscard]] float lengthSquared() const;
    [[nodiscard]] Vector4 normalized() const;

    static const Vector4 Zero;
    static const Vector4 One;
    static const Vector4 Inf;

    float x, y, z, w;
};

Vector4 operator+(const Vector4& v1, const Vector4& v2);
Vector4 operator-(const Vector4& v1, const Vector4& v2);
Vector4 operator-(const Vector4& v);
Vector4 operator*(float scalar, const Vector4& v);
Vector4 operator*(const Vector4& v, float scalar);
Vector4 operator/(const Vector4& v, float scalar);
Vector4& operator+=(Vector4& v1, const Vector4& v2);
Vector4& operator-=(Vector4& v1, const Vector4& v2);
Vector4& operator*=(Vector4& v, float scalar);
Vector4& operator/=(Vector4& v, float scalar);

#endif //QUACK_VECTOR_4_HPP
