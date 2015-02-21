#pragma once
#include "Component.hpp"

struct Position : Component<Position>
{
    float x {0.0};
    float y {0.0};
};
