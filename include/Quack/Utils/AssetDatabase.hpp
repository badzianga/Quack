#ifndef QUACK_ASSET_DATABASE_HPP
#define QUACK_ASSET_DATABASE_HPP
#include "Quack/Utils/UUID.hpp"
#include <filesystem>
#include <unordered_map>

class AssetDatabase {
public:
    /// Load meta files and generate not existing ones.
    static void init(const std::filesystem::path& rootDir);

    /// Get path to asset by UUID.
    static std::filesystem::path getPath(UUID uuid);

    /// Get UUID of asset by path to asset.
    static UUID getUUID(const std::filesystem::path& path);
private:
    static void generateAndLoadMetas(const std::filesystem::path& rootDir);

    static std::unordered_map<UUID, std::filesystem::path> s_metas;

};

#endif //QUACK_ASSET_DATABASE_HPP
