#pragma once
#include <vector>

namespace ECS {
class System;
class SystemStatistics;
class SystemManager
{

public:

    SystemManager(const char* _name);

    void setLatency(float milliseconds);
    void addSystem(System* system);
    void printStats();
    void initialize();
    void update();
    void update(float milliseconds);

private:

    float latency = 0.f;
    float previousUpdateCall = 0.f;

    const char* name;

    SystemStatistics* statistics;

    std::vector<System*> systems = {};
};
}
