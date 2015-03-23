#include "SystemManager.hpp"

namespace ECS {

void SystemManager::addSystem(System *system)
{
    systems.push_back(system);
}

void SystemManager::update(float time)
{
    for (auto system : systems) {
       system->update(time);
    }
}

void SystemManager::update()
{
    for (auto system : systems) {
       system->update();
    }
}
}
