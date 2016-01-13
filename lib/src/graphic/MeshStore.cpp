#include "MeshStore.hpp"
#include "Mesh.hpp"

MeshStore::MeshStore()
    : plan(new Mesh("plan.obj"))
    , cube(new Mesh("cube.obj"))
    , cacodemon(new Mesh("cacodemon.obj"))
    , sphere(new Mesh("sphere.obj"))
{
}

MeshStore::~MeshStore()
{
    delete plan;
    delete cube;
    delete cacodemon;
    delete sphere;
}

Mesh* MeshStore::getMesh(MeshType type)
{
    switch (type) {
        case MeshType::PLAN: return plan;
        case MeshType::CUBE: return cube;
        case MeshType::CACODEMON: return cacodemon;
        case MeshType::SPHERE: return sphere;
    }
}
