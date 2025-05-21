#include "Quack/Graphics/Mesh.hpp"
#include "Quack/Utils/MeshManager.hpp"
#include "Quack/Utils/AssetDatabase.hpp"

std::unordered_map<UUID, Mesh*> MeshManager::s_meshes;

void MeshManager::init() {
    const auto cubeMesh = new Mesh();
    *cubeMesh = Mesh::createCube();
    s_meshes[UUID(UUID::Internal::Cube)] = cubeMesh;

    const auto sphereMesh = new Mesh();
    *sphereMesh = Mesh::createSphere();
    s_meshes[UUID(UUID::Internal::Sphere)] = sphereMesh;

    const auto planeMesh = new Mesh();
    *planeMesh = Mesh::createPlane();
    s_meshes[UUID(UUID::Internal::Plane)] = planeMesh;
}

void MeshManager::destroy() {
    for (auto& [uuid, mesh] : s_meshes) {
        // TODO: make meshes created/destroyed in constructors/destructors
        mesh->destroy();
        delete mesh;
    }
}

const Mesh* MeshManager::get(UUID uuid) {
    if (const auto it = s_meshes.find(uuid); it != s_meshes.end()) {
        return it->second;
    }

    const auto mesh = new Mesh();
    *mesh = Mesh::loadObj(AssetDatabase::getPath(uuid).c_str());
    s_meshes[uuid] = mesh;

    return mesh;
}
