#pragma once
#include <glm/glm.hpp>

struct Movement
{
    float velocity {0.f};
    float spinSpeed {0.f};
    float spin {0.f};

    glm::vec3 position {0.f, 0.f, 0.f};
    glm::vec3 direction {1.f, 0.f, 0.f};
};
