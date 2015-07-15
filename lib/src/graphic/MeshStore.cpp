#include "graphic/MeshStore.hpp"
#include "graphic/Mesh.hpp"

MeshStore::MeshStore()
    : cube(new Mesh("cube.obj"))
    , cacodemon(new Mesh("cacodemon.obj"))
    , flan(new Mesh("flan.obj"))
{
}

Mesh* MeshStore::getMesh(MeshType type)
{
    switch (type) {
        case MeshType::CUBE: return cube;
        case MeshType::CACODEMON: return cacodemon;
        case MeshType::FLAN: return flan;
    }
}
