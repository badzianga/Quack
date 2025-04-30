#include "Quack/Graphics/GlobalLight.hpp"

Color GlobalLight::color = Color::White;
float GlobalLight::ambientIntensity = 0.1f;
glm::vec3 GlobalLight::direction = glm::vec3(1.f, -1.f, -0.5f);
