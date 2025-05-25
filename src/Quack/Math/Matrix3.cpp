#include "Quack/Math/Matrix3.hpp"
#include "Quack/Math/Matrix4.hpp"
#include "Quack/Utils/Logger.hpp"
#include <cassert>

Matrix3::Matrix3() = default;

Matrix3::Matrix3(float scalar) : m_data(
    Vector3(scalar, 0.f, 0.f),
    Vector3(0.f, scalar, 0.f),
    Vector3(0.f, 0.f, scalar)) {}

Matrix3::Matrix3(const Matrix4& mat4) : m_data(Vector3(mat4[0]), Vector3(mat4[1]), Vector3(mat4[2])) {}

const Vector3& Matrix3::operator[](size_t index) const {
    assert(index < 3 && "Index out of bounds");
    return m_data[index];
}

Vector3& Matrix3::operator[](size_t index) {
    assert(index < 3 && "Index out of bounds");
    return m_data[index];
}

const float* Matrix3::get() const {
    return &m_data[0].x;
}

Matrix3 Matrix3::inversed() const {
    float a00 = m_data[0][0], a01 = m_data[1][0], a02 = m_data[2][0];
    float a10 = m_data[0][1], a11 = m_data[1][1], a12 = m_data[2][1];
    float a20 = m_data[0][2], a21 = m_data[1][2], a22 = m_data[2][2];

    float det =
        a00 * (a11 * a22 - a12 * a21) -
        a01 * (a10 * a22 - a12 * a20) +
        a02 * (a10 * a21 - a11 * a20);

    if (det == 0.f) {
        Logger::error() << "Matrix3::inversed(): Matrix is singular";
        return {};
    }

    float invDet = 1.f / det;

    Matrix3 inv;

    inv[0][0] =  (a11 * a22 - a12 * a21) * invDet;
    inv[0][1] = -(a10 * a22 - a12 * a20) * invDet;
    inv[0][2] =  (a10 * a21 - a11 * a20) * invDet;

    inv[1][0] = -(a01 * a22 - a02 * a21) * invDet;
    inv[1][1] =  (a00 * a22 - a02 * a20) * invDet;
    inv[1][2] = -(a00 * a21 - a01 * a20) * invDet;

    inv[2][0] =  (a01 * a12 - a02 * a11) * invDet;
    inv[2][1] = -(a00 * a12 - a02 * a10) * invDet;
    inv[2][2] =  (a00 * a11 - a01 * a10) * invDet;

    return inv;
}

Matrix3 Matrix3::transposed() const {
    Matrix3 result;
    result[0][0] = m_data[0][0];
    result[0][1] = m_data[1][0];
    result[0][2] = m_data[2][0];

    result[1][0] = m_data[0][1];
    result[1][1] = m_data[1][1];
    result[1][2] = m_data[2][1];

    result[2][0] = m_data[0][2];
    result[2][1] = m_data[1][2];
    result[2][2] = m_data[2][2];
    return result;
}
