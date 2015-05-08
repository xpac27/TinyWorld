#pragma once
#include "graphic/MeshType.hpp"

class Mesh;
class MeshStore
{

public:

    MeshStore();

    Mesh* getMesh(MeshType type);

private:

    Mesh* cube;
    Mesh* square;
    Mesh* pyramid;
    Mesh* cacodemon;
    Mesh* goomba;
};
