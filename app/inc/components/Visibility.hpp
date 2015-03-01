#pragma once

#include "ecs/Component.hpp"

struct Visibility : ECS::Component<Visibility> {
    bool active{true};
};
