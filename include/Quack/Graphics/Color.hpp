#ifndef QUACK_COLOR_HPP
#define QUACK_COLOR_HPP

class Color8;

/**
 * @brief Representation of a color using floating-point RGBA components.
 *
 * This class defines a color using red, green, blue, and alpha components
 * in the range of 0.f to 1.f. It also provides several predefined color constants.
 */
class Color {
public:
    /**
     * @brief Default constructor.
     *
     * Initializes the color to transparent (0.f, 0.f, 0.f, 0.f).
     */
    Color();

    /**
     * @brief Construct a color from individual RGBA components.
     *
     * @param red Red component (0.f to 1.f).
     * @param green Green component (0.f to 1.f).
     * @param blue Blue component (0.f to 1.f).
     * @param alpha Alpha component (0.f to 1.f).
     */
    Color(float red, float green, float blue, float alpha);

    /**
     * @brief Construct a color from a Color8 instance.
     *
     * Converts an 8-bit color (0-255 per channel) to floating-point format (0.f-1.f).
     *
     * @param color The 8-bit color to convert.
     */
    Color(const Color8& color);

    /**
     * @brief Convert a Color8 to Color during assignment.
     *
     * Converts an 8-bit color (0-255 per channel) to floating-point format (0.f-1.f).
     *
     * @param color The 8-bit color to convert.
     * @return Reference to the current color.
     */
    Color& operator=(const Color8& color);

    /// Predefined red color (1.f, 0.f, 0.f, 1.f).
    static const Color Red;

    /// Predefined green color (0.f, 1.f, 0.f, 1.f).
    static const Color Green;

    /// Predefined blue color (0.f, 0.f, 1.f, 1.f).
    static const Color Blue;

    /// Predefined yellow color (1.f, 1.f, 0.f, 1.f).
    static const Color Yellow;

    /// Predefined magenta color (1.f, 0.f, 1.f, 1.f).
    static const Color Magenta;

    /// Predefined cyan color (0.f, 1.f, 1.f, 1.f).
    static const Color Cyan;

    /// Predefined white color (1.f, 1.f, 1.f, 1.f).
    static const Color White;

    /// Predefined black color (0.f, 0.f, 0.f, 1.f).
    static const Color Black;

    /// Predefined transparent color (0.f, 0.f, 0.f, 0.f).
    static const Color Transparent;

    /// Red component (0.f to 1.f).
    float r;

    /// Green component (0.f to 1.f).
    float g;

    /// Blue component (0.f to 1.f).
    float b;

    /// Alpha component (0.f to 1.f).
    float a;
};

#endif //QUACK_COLOR_HPP
