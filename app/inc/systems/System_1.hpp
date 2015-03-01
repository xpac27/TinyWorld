#pragma once

#include "ecs/System.hpp"
#include "ecs/Component.hpp"

#include "components/Position.hpp"

class System_1 : public ECS::System
{
public:
    System_1() : System(
            ECS::getComponentTypeMask<Position>()) {}
};
