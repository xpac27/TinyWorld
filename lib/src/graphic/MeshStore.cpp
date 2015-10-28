#include "graphic/MeshStore.hpp"
#include "graphic/Mesh.hpp"

MeshStore::MeshStore()
    // : plan(new Mesh("plan.obj"))
    : cube(new Mesh("cube.obj"))
    // , cacodemon(new Mesh("cacodemon.obj"))
    // , flan(new Mesh("flan.obj"))
{
}

MeshStore::~MeshStore()
{
    delete plan;
    delete cube;
    delete cacodemon;
    delete flan;
}

Mesh* MeshStore::getMesh(MeshType type)
{
    switch (type) {
        case MeshType::PLAN: return cube;
        case MeshType::CUBE: return cube;
        case MeshType::CACODEMON: return cube;
        case MeshType::FLAN: return cube;
    }
}
