#include "SystemManager.hpp"
#include "System.hpp"
#include "utils/Log.hpp"

namespace ECS {

void SystemManager::setLatency(long milliseconds)
{
    latency = milliseconds;
}

void SystemManager::addSystem(System* system)
{
    systems.push_back(system);
}

void SystemManager::initialize()
{
    for (auto system : systems) {
       system->initialize();
    }
}

void SystemManager::update()
{
    for (auto system : systems) {
        system->update();
    }
}

void SystemManager::update(long milliseconds)
{
    if (milliseconds - previousUpdateCall > latency) {
        previousUpdateCall = milliseconds;
        for (auto system : systems) {
            system->update(milliseconds);
        }
    }
}
}
