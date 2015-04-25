#include "graphic/MeshFactory.hpp"
#include "graphic/Mesh.hpp"

MeshFactory::MeshFactory()
    : cube(new Mesh("app/res/cube.obj"))
    , square(new Mesh("app/res/square.obj"))
    , pyramid(new Mesh("app/res/pyramid.obj"))
    , cacodemon(new Mesh("app/res/cacodemon.obj"))
    , goomba(new Mesh("app/res/goomba.obj"))
{
    goomba->debug();
}

Mesh* MeshFactory::getMesh(MeshType type)
{
    switch (type) {
        case MeshType::CUBE: return cube;
        case MeshType::SQUARE: return square;
        case MeshType::PYRAMID: return pyramid;
        case MeshType::GOOMBA: return goomba;
        case MeshType::CACODEMON: return cacodemon;
    }
}
