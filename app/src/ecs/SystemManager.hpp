#pragma once
#include <vector>

namespace ECS {
class System;
class SystemManager
{

public:

    void addSystem(System* system);
    void initialize();
    void update(float time);
    void update();

private:

    std::vector<System*> systems = {};
};
}
