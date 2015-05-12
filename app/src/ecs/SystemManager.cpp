#include "SystemManager.hpp"
#include "SystemStatistics.hpp"
#include "System.hpp"
#include "utils/Log.hpp"


using namespace Log;

namespace ECS {

SystemManager::SystemManager(const char* _name)
    : name(_name)
    , statistics(new SystemStatistics())
{}

void SystemManager::setLatency(float milliseconds)
{
    latency = milliseconds;
}

void SystemManager::addSystem(System* system)
{
    systems.push_back(system);
}

void SystemManager::printStats()
{
    statistics->print(name);
}

void SystemManager::initialize()
{
    for (auto system : systems) {
       system->initialize();
    }
}

void SystemManager::update()
{
    statistics->updating(); // TODO wrap that in the for loop and stat all systems
    for (auto system : systems) {
        system->update();
    }
    statistics->updated();
}

void SystemManager::update(float milliseconds)
{
    if (milliseconds - previousUpdateCall > latency) {
        float delta = float(milliseconds - previousUpdateCall) / 1000.f;
        statistics->updating();
        previousUpdateCall = milliseconds;
        for (auto system : systems) {
            system->update(milliseconds, delta);
        }
        statistics->updated();
    }
}
}
