#pragma once

#include "ecs/System.hpp"
#include "ecs/Component.hpp"

#define mask(n) ((1) << (n))

class System_1 : public ECS::System
{
public:
    // TODO use variadic template with component class name directly System(Position, Life)
    // https://github.com/miguelmartin75/anax/blob/master/include/anax/ComponentFilter.hpp#L99
    System_1() : System(mask(ECS::Component<Position>::typeIndex)) {}
};
