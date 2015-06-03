#include "graphic/MeshStore.hpp"
#include "graphic/Mesh.hpp"

MeshStore::MeshStore()
    // : cube(new Mesh("cube.obj"))
    // , square(new Mesh("square.obj"))
    // , pyramid(new Mesh("pyramid.obj"))
    // , cacodemon(new Mesh("cacodemon.obj"))
    // , goomba(new Mesh("goomba.obj"))
    : flan(new Mesh("flan.obj"))
{
    flan->debug();
}

Mesh* MeshStore::getMesh(MeshType type)
{
    switch (type) {
        case MeshType::CUBE: return cube;
        case MeshType::SQUARE: return square;
        case MeshType::PYRAMID: return pyramid;
        case MeshType::GOOMBA: return goomba;
        case MeshType::CACODEMON: return cacodemon;
        case MeshType::FLAN: return flan;
    }
}
