#ifndef QUACK_ASSET_DATABASE_HPP
#define QUACK_ASSET_DATABASE_HPP
#include "Quack/Utils/UUID.hpp"
#include <filesystem>
#include <unordered_map>

class AssetDatabase {
public:
    static void init();
private:
    static void generateAndLoadMetas();
};

#endif //QUACK_ASSET_DATABASE_HPP
