#include "Shape.hpp"

Shape::Shape()
{
    meshes[0] = Mesh();
}

void Shape::draw()
{
    meshes[0].draw();
}
