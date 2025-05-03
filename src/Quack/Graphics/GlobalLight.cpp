#include "Quack/Graphics/GlobalLight.hpp"

Color GlobalLight::color = Color::White;
float GlobalLight::ambientIntensity = 0.1f;
Vector3 GlobalLight::direction = { 1.f, -1.f, -0.5f };
