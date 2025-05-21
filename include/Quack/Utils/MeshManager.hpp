#ifndef QUACK_MESH_MANAGER_HPP
#define QUACK_MESH_MANAGER_HPP
#include "Quack/Utils/UUID.hpp"
#include <unordered_map>

class Mesh;

class MeshManager {
public:
    static void init();
    static void destroy();
    static const Mesh* get(UUID uuid);
private:
    static std::unordered_map<UUID, Mesh*> s_meshes;
};

#endif //QUACK_MESH_MANAGER_HPP
