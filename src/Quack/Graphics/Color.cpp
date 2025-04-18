#include "Quack/Graphics/Color.hpp"
#include "Quack/Graphics/Color8.hpp"

Color::Color() : r(0.f), g(0.f), b(0.f), a(0.f) {}

Color::Color(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha) {}

Color::Color(const Color8& color) :
    r(static_cast<float>(color.r) / 255.f),
    g(static_cast<float>(color.g) / 255.f),
    b(static_cast<float>(color.b) / 255.f),
    a(static_cast<float>(color.a) / 255.f) {}

Color& Color::operator=(const Color8& color) {
    r = static_cast<float>(color.r) / 255.f;
    g = static_cast<float>(color.g) / 255.f;
    b = static_cast<float>(color.b) / 255.f;
    a = static_cast<float>(color.a) / 255.f;

    return *this;
}

const Color Color::Red{ 1.f, 0.f, 0.f, 1.f };
const Color Color::Green{ 0.f, 1.f, 0.f, 1.f };
const Color Color::Blue{ 0.f, 0.f, 1.f, 1.f };
const Color Color::Yellow{ 1.f, 1.f, 0.f, 1.f };
const Color Color::Magenta{ 1.f, 0.f, 1.f, 1.f };
const Color Color::Cyan{ 0.f, 1.f, 1.f, 1.f };
const Color Color::White{ 1.f, 1.f, 1.f, 1.f };
const Color Color::Black{ 0.f, 0.f, 0.f, 1.f };
const Color Color::Transparent{ 0.f, 0.f, 0.f, 0.f };
