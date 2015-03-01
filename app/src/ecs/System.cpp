#include "ecs/System.hpp"

void ECS::System::registerEntity(unsigned int entity)
{
    entities.push_back(entity);
}

void ECS::System::unregisterEntity(unsigned int entity)
{
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) entities.erase(it);
}

bool ECS::System::useComponent(unsigned int mask) const
{
    return componentTypes & mask;
}
