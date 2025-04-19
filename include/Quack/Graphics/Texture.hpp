#ifndef QUACK_TEXTURE_HPP
#define QUACK_TEXTURE_HPP
#include <cstdint>

class Texture {
public:
    Texture();
    bool create(const char* filename);
    bool destroy();
    void bind(uint32_t unit = 0) const;
    static void unbind();
private:
    void generate();
    bool loadFromFile(const char* filename);

    uint32_t m_id;
};

#endif //QUACK_TEXTURE_HPP
