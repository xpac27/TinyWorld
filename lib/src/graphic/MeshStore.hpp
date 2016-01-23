#pragma once
#include "../../inc/graphic/MeshType.hpp"

class Mesh;
class MeshStore
{

public:

    MeshStore();
    ~MeshStore();

    Mesh* getMesh(MeshType type);

    void reloadMeshesTextures();

private:

    Mesh* plan;
    Mesh* cube;
    Mesh* torus;
    Mesh* sphere;
    Mesh* teapot;
};
