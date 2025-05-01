// This file includes code snippets from:
// G-Truc Creation (c) 2005, licensed under the MIT License
// Full license available in the link below.
// https://github.com/g-truc/glm/blob/master/copying.txt

#include "Quack/Math/Matrix4.hpp"
#include "Quack/Math/Vector3.hpp"
#include <cassert>
#include <cmath>

Matrix4::Matrix4() = default;

Matrix4::Matrix4(float scalar) : m_data(
    Vector4(scalar, 0.f, 0.f, 0.f),
    Vector4(0.f, scalar, 0.f, 0.f),
    Vector4(0.f, 0.f, scalar, 0.f),
    Vector4(0.f, 0.f, 0.f, scalar)) {}

const Vector4& Matrix4::operator[](size_t index) const {
    assert(index < 4 && "Index out of bounds");
    return m_data[index];
}

Vector4& Matrix4::operator[](size_t index) {
    assert(index < 4 && "Index out of bounds");
    return m_data[index];
}

void Matrix4::translate(const Vector3& translation) {
    m_data[3] = m_data[0] * translation[0] + m_data[1] * translation[1] + m_data[2] * translation[2] + m_data[3];
}

void Matrix4::rotate(float angle, const Vector3& rotationAxis) {
    const float c = std::cos(angle);
    const float s = std::sin(angle);

    const Vector3 axis = rotationAxis.normalized();
    const Vector3 temp((1.f - c) * axis);

    Matrix4 rot;
    rot[0][0] = c + temp[0] * axis[0];
    rot[0][1] = temp[0] * axis[1] + s * axis[2];
    rot[0][2] = temp[0] * axis[2] - s * axis[1];

    rot[1][0] = temp[1] * axis[0] - s * axis[2];
    rot[1][1] = c + temp[1] * axis[1];
    rot[1][2] = temp[1] * axis[2] + s * axis[0];

    rot[2][0] = temp[2] * axis[0] + s * axis[1];
    rot[2][1] = temp[2] * axis[1] - s * axis[0];
    rot[2][2] = c + temp[2] * axis[2];

    const Vector4 col0 = m_data[0];
    const Vector4 col1 = m_data[1];
    const Vector4 col2 = m_data[2];

    m_data[0] = col0 * rot[0][0] + col1 * rot[0][1] + col2 * rot[0][2];
    m_data[1] = col0 * rot[1][0] + col1 * rot[1][1] + col2 * rot[1][2];
    m_data[2] = col0 * rot[2][0] + col1 * rot[2][1] + col2 * rot[2][2];
}

void Matrix4::scale(const Vector3& scale) {
    m_data[0] *= scale[0];
    m_data[1] *= scale[1];
    m_data[2] *= scale[2];
}

Matrix4 Matrix4::translated(const Vector3& translation) const {
    Matrix4 result(*this);
    result[3] = m_data[0] * translation[0] + m_data[1] * translation[1] + m_data[2] * translation[2] + m_data[3];
    return result;
}

Matrix4 Matrix4::rotated(float angle, const Vector3& rotationAxis) const {
    const float c = std::cos(angle);
    const float s = std::sin(angle);

    const Vector3 axis = rotationAxis.normalized();
    const Vector3 temp((1.f - c) * axis);

    Matrix4 rot;
    rot[0][0] = c + temp[0] * axis[0];
    rot[0][1] = temp[0] * axis[1] + s * axis[2];
    rot[0][2] = temp[0] * axis[2] - s * axis[1];

    rot[1][0] = temp[1] * axis[0] - s * axis[2];
    rot[1][1] = c + temp[1] * axis[1];
    rot[1][2] = temp[1] * axis[2] + s * axis[0];

    rot[2][0] = temp[2] * axis[0] + s * axis[1];
    rot[2][1] = temp[2] * axis[1] - s * axis[0];
    rot[2][2] = c + temp[2] * axis[2];

    Matrix4 result(*this);
    result[0] = m_data[0] * rot[0][0] + m_data[1] * rot[0][1] + m_data[2] * rot[0][2];
    result[1] = m_data[0] * rot[1][0] + m_data[1] * rot[1][1] + m_data[2] * rot[1][2];
    result[2] = m_data[0] * rot[2][0] + m_data[1] * rot[2][1] + m_data[2] * rot[2][2];
    return result;
}

Matrix4 Matrix4::scaled(const Vector3& scale) const {
    Matrix4 result(*this);
    result[0] *= scale[0];
    result[1] *= scale[1];
    result[2] *= scale[2];
    return result;
}

const float* Matrix4::get() const {
    return &m_data[0].x;
}

const Matrix4 Matrix4::Identity{ 1.f };
