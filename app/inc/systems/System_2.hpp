#pragma once
#include "System.hpp"
#include "Component.hpp"

#define mask(n) ((1) << (n))

class System_2 : public System
{
    public:
        System_2() :System(
                mask(Component<Position>::typeIndex) | 
                mask(Component<Life>::typeIndex)) {}
};
