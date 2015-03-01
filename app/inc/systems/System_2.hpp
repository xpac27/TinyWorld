#pragma once

#include "ecs/System.hpp"
#include "ecs/Component.hpp"

#define mask(n) ((1) << (n))

class System_2 : public ECS::System
{
public:
    System_2() : System(mask(ECS::Component<Position>::typeIndex) | mask(ECS::Component<Life>::typeIndex)) {}
};
