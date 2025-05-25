#include "Quack/Utils/TextureManager.hpp"
#include "Quack/Utils/AssetDatabase.hpp"
#include "Quack/Utils/Logger.hpp"

std::unordered_map<UUID, Texture*> TextureManager::s_textures;

void TextureManager::init() {
    Logger::debug() << "TextureManager initialized";
}

void TextureManager::destroy() {
    for (auto& [uuid, texture] : s_textures) {
        // TODO: make textures created/destroyed in constructors/destructors
        texture->destroy();
        delete texture;
    }
    Logger::debug() << "TextureManager destroyed - destroyed all textures";
}

Texture* TextureManager::get(UUID uuid) {
    if (const auto it = s_textures.find(uuid); it != s_textures.end()) {
        return it->second;
    }

    const auto texture = new Texture();
    texture->create(AssetDatabase::getPath(uuid).c_str());
    s_textures[uuid] = texture;

    return texture;
}
