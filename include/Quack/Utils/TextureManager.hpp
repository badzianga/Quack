#ifndef QUACK_TEXTURE_MANAGER_HPP
#define QUACK_TEXTURE_MANAGER_HPP
#include "Quack/Graphics/Texture.hpp"
#include "Quack/Utils/UUID.hpp"
#include <unordered_map>

class TextureManager {
public:
    static void init();
    static void destroy();
    static Texture* get(UUID uuid);
private:
    static std::unordered_map<UUID, Texture*> s_textures;
};

#endif //QUACK_TEXTURE_MANAGER_HPP
