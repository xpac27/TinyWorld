#include "../../inc/ecs/System.hpp"
#include "../../inc/ecs/ComponentManagerBase.hpp"
#include "../utils/Signal.hpp"
#include "../utils/log.hpp"
#include <algorithm>

namespace ecs {

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
