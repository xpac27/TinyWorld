#pragma once
#include "graphic/Mesh.hpp"
#include "graphic/MeshType.hpp"

class MeshFactory
{

public:

    Mesh* getMesh(MeshType type);

private:

    Mesh cube = Mesh("app/res/cube.obj");
    Mesh diamond = Mesh("app/res/diamond.obj");
};
