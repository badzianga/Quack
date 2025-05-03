#ifndef QUACK_MATH_HPP
#define QUACK_MATH_HPP

class Matrix4;
class Vector3;

namespace Math {

float toRadians(float degrees);

float toDegrees(float radians);

Matrix4 lookAt(Vector3 eye, Vector3 target, Vector3 up);

} // Math

#endif //QUACK_MATH_HPP
