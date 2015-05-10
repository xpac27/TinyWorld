#pragma once
#include <vector>

namespace ECS {
class System;
class SystemStatistics;
class SystemManager
{

public:

    SystemManager(const char* _name);

    void setLatency(long milliseconds);
    void addSystem(System* system);
    void printStats();
    void initialize();
    void update();
    void update(long milliseconds);

private:

    long latency = 0;
    long previousUpdateCall = 0;

    const char* name;

    SystemStatistics* statistics;

    std::vector<System*> systems = {};
};
}
