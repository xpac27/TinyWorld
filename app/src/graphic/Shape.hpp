#pragma once
#include "Mesh.hpp"

// TODO rename to mesh manager
class Shape
{

public:

    // TODO pass which mesh type to use
    Shape();

    void draw();

private:

    const unsigned int type;

    // TODO maintain a static dictionay of meshes
    // define const types for 0, 1, 2, 3 (TRIANGLE, SQUARE, MONSTER...)
    Mesh meshes[1];
};
