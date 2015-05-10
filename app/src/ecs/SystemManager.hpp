#pragma once
#include <vector>

namespace ECS {
class System;
class SystemManager
{

public:

    void setLatency(long milliseconds);
    void addSystem(System* system);
    void initialize();
    void update();
    void update(long milliseconds);

private:

    long latency = 0;
    long previousUpdateCall = 0;

    std::vector<System*> systems = {};
};
}
