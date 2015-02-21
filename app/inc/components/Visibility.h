#pragma once
#include "Component.h"

class Component;
struct Visibility : Component<Visibility>
{
    bool active {true};
};
