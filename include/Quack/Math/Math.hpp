#ifndef QUACK_MATH_HPP
#define QUACK_MATH_HPP

class Matrix4;
class Vector3;

namespace Math {

float toRadians(float degrees);

float toDegrees(float radians);

float clamp(float value, float min, float max);

Matrix4 lookAt(Vector3 eye, Vector3 target, Vector3 up);

Matrix4 perspective(float fov, float aspect, float near, float far);

Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);

} // Math

#endif //QUACK_MATH_HPP
