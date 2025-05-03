#ifndef QUACK_VECTOR_3_HPP
#define QUACK_VECTOR_3_HPP
#include <cstddef>

class Vector2;

class Vector3 {
public:
    Vector3();
    Vector3(float scalar);
    Vector3(Vector2 v, float z);
    Vector3(float x, float y, float z);

    float& operator[](size_t index);
    const float& operator[](size_t index) const;

    [[nodiscard]] Vector3 directionTo(const Vector3& to) const;
    [[nodiscard]] float distanceTo(const Vector3& to) const;
    [[nodiscard]] float distanceToSquared(const Vector3& to) const;
    [[nodiscard]] float length() const;
    [[nodiscard]] float lengthSquared() const;
    [[nodiscard]] Vector3 normalized() const;

    [[nodiscard]] static float dot(const Vector3& left, const Vector3& right);
    [[nodiscard]] static Vector3 cross(const Vector3& left, const Vector3& right);

    static const Vector3 Zero;
    static const Vector3 One;
    static const Vector3 Inf;
    static const Vector3 Left;
    static const Vector3 Right;
    static const Vector3 Up;
    static const Vector3 Down;
    static const Vector3 Forward;
    static const Vector3 Back;

    float x, y, z;
};

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v);
Vector3 operator*(float scalar, const Vector3& v);
Vector3 operator*(const Vector3& v, float scalar);
Vector3 operator/(const Vector3& v, float scalar);
Vector3& operator+=(Vector3& v1, const Vector3& v2);
Vector3& operator-=(Vector3& v1, const Vector3& v2);
Vector3& operator*=(Vector3& v, float scalar);
Vector3& operator/=(Vector3& v, float scalar);

#endif //QUACK_VECTOR_3_HPP
