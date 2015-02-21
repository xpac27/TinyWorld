#pragma once
#include "Component.h"

class Component;
struct Life : Component<Life>
{
    int amount {123};
};
