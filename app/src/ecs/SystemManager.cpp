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

void SystemManager::setLatency(float seconds)
{
    latency = seconds;
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

void SystemManager::update(float seconds)
{
    if (seconds - previousUpdateCall > latency) {
        float delta = seconds - previousUpdateCall;
        statistics->updating();
        previousUpdateCall = seconds;
        for (auto system : systems) {
            system->update(seconds, delta);
        }
        statistics->updated();
    }
}
}
