#pragma once
#include "Component.h"

class Component;
struct Position : Component<Position>
{
    float x {0.0};
    float y {0.0};
};
