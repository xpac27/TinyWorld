#pragma once
#include "Component.hpp"

struct Visibility : Component<Visibility> {
    bool active{true};
};
