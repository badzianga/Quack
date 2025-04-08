#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
public:
    Renderer() = delete;
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    static void clear(float red, float green, float blue, float alpha);
    static void drawTestTriangle();
};

#endif //RENDERER_HPP
