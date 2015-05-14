#pragma once
#include "graphic/MeshType.hpp"
#include <glm/vec3.hpp>

struct Visibility
{
    MeshType meshType { MeshType::CACODEMON };

    glm::vec3 scale {1.f, 1.f, 1.f};
};
