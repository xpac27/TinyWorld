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
    }
}

void System::onEntityRemoved(id entity)
{
    entities.erase(std::find(entities.begin(), entities.end(), entity));
}

void System::update()
{
    // Nothing to do...
}

void System::update(float /*milliseconds*/, float /*delta*/)
{
    // Nothing to do...
}

void System::initialize()
{
    // Nothing to do...
}

std::vector<id>* System::getEntities()
{
    return &entities;
}
}
