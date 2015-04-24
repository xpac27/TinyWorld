#pragma once
#include "graphic/MeshType.hpp"

class Mesh;
class MeshFactory // TODO rename MeshStore
{

public:

    MeshFactory();

    Mesh* getMesh(MeshType type);

private:

    Mesh* cube;
    Mesh* square;
    Mesh* pyramid;
    Mesh* cacodemon;
    Mesh* goomba;
};
