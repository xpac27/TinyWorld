#include "MeshStore.hpp"
#include "Mesh.hpp"

MeshStore::MeshStore()
    : plan(new Mesh("plan.obj"))
    , cube(new Mesh("cube.obj"))
    , wingedVictory(new Mesh("winged_victory.obj"))
    , sphere(new Mesh("sphere.obj"))
{
}

MeshStore::~MeshStore()
{
    delete plan;
    delete cube;
    delete wingedVictory;
    delete sphere;
}

Mesh* MeshStore::getMesh(MeshType type)
{
    switch (type) {
        case MeshType::PLAN: return plan;
        case MeshType::CUBE: return cube;
        case MeshType::WINGED_VICTORY: return wingedVictory;
        case MeshType::SPHERE: return sphere;
    }
}
