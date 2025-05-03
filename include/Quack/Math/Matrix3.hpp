#ifndef QUACK_MATRIX_3_HPP
#define QUACK_MATRIX_3_HPP
#include "Quack/Math/Vector3.hpp"

class Matrix4;

class Matrix3 {
public:
    Matrix3();
    Matrix3(float scalar);
    Matrix3(const Matrix4& mat4);

    const Vector3& operator[](size_t index) const;
    Vector3& operator[](size_t index);
    [[nodiscard]] const float* get() const;

    [[nodiscard]] Matrix3 inversed() const;
    [[nodiscard]] Matrix3 transposed() const;

    static const Matrix3 Identity;
private:
    Vector3 m_data[3];
};

#endif //QUACK_MATRIX_3_HPP
