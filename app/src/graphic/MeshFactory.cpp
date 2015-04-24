#include "graphic/MeshFactory.hpp"
#include "graphic/Mesh.hpp"

MeshFactory::MeshFactory()
    : cube(new Mesh("app/res/cube.obj"))
    , square(new Mesh("app/res/square.obj"))
    , pyramid(new Mesh("app/res/pyramid.obj"))
    , pig(new Mesh("app/res/pig.obj"))
{}

Mesh* MeshFactory::getMesh(MeshType type)
{
    switch (type) {
        case MeshType::CUBE: return cube;
        case MeshType::SQUARE: return square;
        case MeshType::PYRAMID: return pyramid;
        case MeshType::PIG: return pig;
    }
}
