#pragma once
#include "System.h"
#include "Component.h"

#define mask(n) ((1) << (n))

class System_1 : public System
{
    public:
        System_1() :System(
                mask(Component<Position>::typeIndex)) {}
};
