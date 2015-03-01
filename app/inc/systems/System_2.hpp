#pragma once

#include "ecs/System.hpp"
#include "ecs/Component.hpp"

#include "components/Position.hpp"
#include "components/Life.hpp"

class System_2 : public ECS::System
{
public:
    System_2() : System(
            ECS::getComponentMask<Position>() |
            ECS::getComponentMask<Life>()) {}
};
