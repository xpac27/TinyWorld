#pragma once
#include "graphic/Mesh.hpp"
#include "graphic/MeshType.hpp"

// TODO rename MeshStore
class MeshFactory
{

public:

    Mesh* getMesh(MeshType type);

private:

    Mesh cube = Mesh("app/res/cube.obj");
    Mesh square = Mesh("app/res/square.obj");
    Mesh pyramid = Mesh("app/res/pyramid.obj");
};
