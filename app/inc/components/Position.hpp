#pragma once

#include "ecs/Component.hpp"

struct Position : ECS::Component<Position> {
    float x{0.0};
    float y{0.0};
};
