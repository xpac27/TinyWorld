#include "Random.hpp"
#include <stdlib.h>

float Random::get()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float Random::get(float max)
{
    return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / max));
}

float Random::get(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(max-min)));
}
