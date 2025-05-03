// This file includes code snippets from:
// GLM, G-Truc Creation (c) 2005, licensed under the MIT License
// Full license available in the link below.
// https://github.com/g-truc/glm/blob/master/copying.txt

#include "Quack/Math/Math.hpp"
#include "Quack/Math/Matrix4.hpp"
#include "Quack/Math/Vector3.hpp"
#include <cassert>
#include <cmath>

float Math::toRadians(float degrees) {
    return degrees * static_cast<float>(M_PI) / 180.f;
}

float Math::toDegrees(float radians) {
    return radians * 180.f / static_cast<float>(M_PI);
}

float Math::clamp(float value, float low, float high) {
    return std::max(low, std::min(high, value));
}

Matrix4 Math::lookAt(Vector3 eye, Vector3 target, Vector3 up) {
    const Vector3 f = (target - eye).normalized();
    const Vector3 s = (Vector3::cross(f, up)).normalized();
    const Vector3 u = Vector3::cross(s, f);

    Matrix4 result = Matrix4::Identity;
    result[0][0] = s.x;
    result[1][0] = s.y;
    result[2][0] = s.z;
    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;
    result[0][2] = -f.x;
    result[1][2] = -f.y;
    result[2][2] = -f.z;
    result[3][0] = -Vector3::dot(s, eye);
    result[3][1] = -Vector3::dot(u, eye);
    result[3][2] = Vector3::dot(f, eye);
    return result;
}

Matrix4 Math::perspective(float fov, float aspect, float near, float far) {
    assert(std::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.f);

    float tanHalfFov = std::tan(fov / 2.f);

    Matrix4 result;
    result[0][0] = 1.f / (aspect * tanHalfFov);
    result[1][1] = 1.f / (tanHalfFov);
    result[2][2] = - (far + near) / (far - near);
    result[2][3] = - 1.f;
    result[3][2] = - (2.f * far * near) / (far - near);
    return result;
}

Matrix4 Math::orthographic(float left, float right, float bottom, float top, float near, float far) {
    Matrix4 result = Matrix4::Identity;
    result[0][0] = 2.f / (right - left);
    result[1][1] = 2.f / (top - bottom);
    result[2][2] = -2.f / (far - near);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(far + near) / (far - near);
    return result;
}
