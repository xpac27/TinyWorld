#pragma once
#include <vector>
#include "System.hpp"

namespace ECS {

class SystemManager
{

public:

    void addSystem(System *system);
    void update(float time);
    void update();

private:

    std::vector<System*> systems = {};
};
}
