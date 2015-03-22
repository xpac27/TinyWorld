#pragma once

#include "ecs/Component.hpp"

struct Life : ECS::Component<Life> {
    int amount{123};
};
