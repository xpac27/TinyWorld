#include "graphic/MeshFactory.hpp"

Mesh* MeshFactory::getMesh(MeshType type)
{
    switch (type) {
        case MeshType::CUBE: return &cube;
        case MeshType::DIAMOND: return &diamond;
    }
}
