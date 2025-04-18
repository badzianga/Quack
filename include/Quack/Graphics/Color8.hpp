#ifndef QUACK_COLOR_8_HPP
#define QUACK_COLOR_8_HPP
#include <cstdint>

class Color;

/**
 * @brief Representation of a color using 8-bit RGBA components.
 *
 * This class stores color data with red, green, blue, and alpha components,
 * each represented as an unsigned 8-bit integer (0–255).
 */
class Color8 {
public:
    /**
     * @brief Default constructor.
     *
     * Initializes the color to transparent (0, 0, 0, 0).
     */
    Color8();

    /**
     * @brief Construct a color from individual 8-bit RGBA components.
     *
     * @param red Red component (0–255).
     * @param green Green component (0–255).
     * @param blue Blue component (0–255).
     * @param alpha Alpha component (0–255).
     */
    Color8(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    /**
     * @brief Construct a color from a floating-point Color.
     *
     * Converts the floating-point values (0.f–1.f) of a Color to 8-bit integers (0–255).
     *
     * @param color The floating-point color to convert.
     */
    Color8(const Color& color);

    /**
     * @brief Convert a Color to Color8 during assignment.
     *
     * Converts and assigns a floating-point Color to this 8-bit color.
     *
     * @param color The Color to assign from.
     * @return Reference to the current color.
     */
    Color8& operator=(const Color& color);

    /// Predefined red color (255, 0, 0, 255).
    static const Color8 Red;

    /// Predefined green color (0, 255, 0, 255).
    static const Color8 Green;

    /// Predefined blue color (0, 0, 255, 255).
    static const Color8 Blue;

    /// Predefined yellow color (255, 255, 0, 255).
    static const Color8 Yellow;

    /// Predefined magenta color (255, 0, 255, 255).
    static const Color8 Magenta;

    /// Predefined cyan color (0, 255, 255, 255).
    static const Color8 Cyan;

    /// Predefined white color (255, 255, 255, 255).
    static const Color8 White;

    /// Predefined black color (0, 0, 0, 255).
    static const Color8 Black;

    /// Predefined transparent color (0, 0, 0, 0).
    static const Color8 Transparent;

    /// Red component (0–255).
    uint8_t r;

    /// Green component (0–255).
    uint8_t g;

    /// Blue component (0–255).
    uint8_t b;

    /// Alpha component (0–255).
    uint8_t a;
};

#endif //QUACK_COLOR_8_HPP
