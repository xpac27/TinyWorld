#pragma once
#include <vector>

namespace ECS {
class System;
class SystemStatistics;
class SystemManager
{

public:

    SystemManager(const char* _name);

    void setLatency(double milliseconds);
    void addSystem(System* system);
    void printStats();
    void initialize();
    void update();
    void update(double milliseconds);

private:

    double latency = 0;
    double previousUpdateCall = 0;

    const char* name;

    SystemStatistics* statistics;

    std::vector<System*> systems = {};
};
}
