#include "MeshStore.hpp"
#include "Mesh.hpp"

MeshStore::MeshStore()
    : plan(new Mesh("plan.obj"))
    , cube(new Mesh("cube.obj"))
    , torus(new Mesh("torus.obj"))
    , sphere(new Mesh("sphere.obj"))
    , teapot(new Mesh("teapot.obj"))
{
}

MeshStore::~MeshStore()
{
    delete plan;
    delete cube;
    delete torus;
    delete sphere;
    delete teapot;
}

Mesh* MeshStore::getMesh(MeshType type)
{
    switch (type) {
        case MeshType::PLAN: return plan;
        case MeshType::CUBE: return cube;
        case MeshType::TORUS: return torus;
        case MeshType::SPHERE: return sphere;
        case MeshType::TEAPOT: return teapot;
    }
}
