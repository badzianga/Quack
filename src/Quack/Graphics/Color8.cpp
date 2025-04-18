#include "Quack/Graphics/Color8.hpp"
#include "Quack/Graphics/Color.hpp"

Color8::Color8() : r(0), g(0), b(0), a(0) {}

Color8::Color8(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : r(red), g(green), b(blue), a(alpha) {}

Color8::Color8(const Color& color) :
   r(static_cast<uint8_t>(color.r * 255.f)),
   g(static_cast<uint8_t>(color.g * 255.f)),
   b(static_cast<uint8_t>(color.b * 255.f)),
   a(static_cast<uint8_t>(color.a * 255.f)) {}

Color8& Color8::operator=(const Color& color) {
   r = static_cast<uint8_t>(color.r * 255.f);
   g = static_cast<uint8_t>(color.g * 255.f);
   b = static_cast<uint8_t>(color.b * 255.f);
   a = static_cast<uint8_t>(color.a * 255.f);

   return *this;
}

const Color8 Color8::Red{ 255, 0, 0, 255 };
const Color8 Color8::Green{ 0, 255, 0, 255 };
const Color8 Color8::Blue{ 0, 0, 255, 255 };
const Color8 Color8::Yellow{ 255, 255, 0, 255 };
const Color8 Color8::Magenta{ 255, 0, 255, 255 };
const Color8 Color8::Cyan{ 0, 255, 255, 255 };
const Color8 Color8::White{ 255, 255, 255, 255 };
const Color8 Color8::Black{ 0, 0, 0, 255 };
const Color8 Color8::Transparent{ 0, 0, 0, 0 };
