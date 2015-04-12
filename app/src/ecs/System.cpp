#include <algorithm>
#include "System.hpp"
#include "helpers/Debug.hpp"

namespace ECS {

System::System(std::initializer_list<ComponentManagerBase*> c)
{
    for (auto componentManager : c) {
        componentManager->getEntityAddedSignal()->addCallback(this, &System::onEntityAdded);
        componentManager->getEntityRemovedSignal()->addCallback(this, &System::onEntityRemoved);
    }
}

void System::onEntityAdded(id entity)
{
    if (std::find(entities.begin(), entities.end(), entity) == entities.end()) {
        entities.push_back(entity);
    }
}

void System::onEntityRemoved(id entity)
{
    entities.erase(std::find(entities.begin(), entities.end(), entity));
}

void System::update(float /*time*/)
{
    Debug::printl("Warning: update(time) function called but not implemented by System");
}

void System::initialize()
{
    Debug::printl("Warning: initialize() function called but not implemented by System");
}

void System::update()
{
    Debug::printl("Warning: update() function called but not implemented by System");
}

std::vector<id>* System::getEntities()
{
    return &entities;
}
}
