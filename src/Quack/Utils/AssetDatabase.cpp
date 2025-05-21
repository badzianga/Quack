#include "Quack/Utils/AssetDatabase.hpp"
#include "Quack/Utils/Logger.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

static std::unordered_map<UUID, std::filesystem::path> s_metas;

void AssetDatabase::init() {
    generateAndLoadMetas();
}

void AssetDatabase::generateAndLoadMetas() {
    for (const auto& entry : fs::recursive_directory_iterator("./Assets")) {
        if (!entry.is_regular_file()) continue;

        const fs::path& filePath = entry.path();
        if (filePath.extension() == ".meta") {
            // check if corresponding asset file exists
            fs::path assetPath = filePath;
            assetPath.replace_extension("");
            if (!fs::exists(assetPath)) {
                // remove this .meta file
                fs::remove(filePath);
                Logger::debug("Removed .meta file: " + filePath.string());
                continue;
            }

            // load this meta file and connect assetPath to corresponding UUID
            std::ifstream metaFile(filePath);
            nlohmann::json json;
            metaFile >> json;
            metaFile.close();
            s_metas[UUID(json["uuid"])] = assetPath;
            Logger::debug("Loaded .meta file: " + filePath.string());
        }
        else {
            // check if corresponding .meta file exists
            fs::path metaPath = filePath;
            metaPath += ".meta";
            if (!fs::exists(metaPath)) {
                // create this .meta file
                std::ofstream metaFile(metaPath);
                UUID uuid;
                nlohmann::json json;
                json["uuid"] = static_cast<uint64_t>(uuid);
                metaFile << json.dump(2);
                metaFile.close();

                // add this meta file and connect assetPath to corresponding UUID
                s_metas[uuid] = filePath;
                Logger::debug("Created .meta file and loaded it: " + metaPath.string());
            }
        }
    }
}
