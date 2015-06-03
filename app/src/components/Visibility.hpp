#pragma once
#include "graphic/MeshType.hpp"
#include <glm/vec3.hpp>

struct Visibility
{
    MeshType meshType { MeshType::FLAN };

    glm::vec3 scale {30.f, 30.f, 30.f};
};
