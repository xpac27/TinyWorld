#include "System.hpp"
#include "ComponentManagerBase.hpp"
#include "utils/Log.hpp"
#include <algorithm>

using namespace Log;

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
        entityAdded(entity);
    }
}

void System::onEntityRemoved(id entity)
{
    if (std::find(entities.begin(), entities.end(), entity) != entities.end()) {
        entities.erase(std::find(entities.begin(), entities.end(), entity));
        entityRemoved(entity);
    }
}

void System::update()
{
    // Nothing to do...
}

void System::update(float /*seconds*/, float /*delta*/)
{
    // Nothing to do...
}

void System::initialize()
{
    // Nothing to do...
}

void System::entityAdded(id /*entity*/)
{
    // Nothing to do...
}

void System::entityRemoved(id /*entity*/)
{
    // Nothing to do...
}

std::vector<id>* System::getEntities()
{
    return &entities;
}
}
