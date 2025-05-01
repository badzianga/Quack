#ifndef QUACK_MATRIX_4_HPP
#define QUACK_MATRIX_4_HPP
#include "Vector4.hpp"
#include <cstddef>

class Matrix4 {
public:
    Matrix4();
    Matrix4(float scalar);

    const Vector4& operator[](size_t index) const;
    Vector4& operator[](size_t index);
    [[nodiscard]] const float* get() const;

    void translate(const Vector3& translation);
    void rotate(float angle, const Vector3& rotationAxis);
    void scale(const Vector3& scale);

    [[nodiscard]] Matrix4 translated(const Vector3& translation) const;
    [[nodiscard]] Matrix4 rotated(float angle, const Vector3& rotationAxis) const ;
    [[nodiscard]] Matrix4 scaled(const Vector3& scale) const;

    // Matrix4 perspective(float fov, float aspect, float near, float far);
    // Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);

    static const Matrix4 Identity;
private:
    Vector4 m_data[4];
};

#endif //QUACK_MATRIX_4_HPP
