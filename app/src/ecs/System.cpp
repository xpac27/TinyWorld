#include "System.hpp"
#include "helpers/Debug.hpp"

namespace ECS {

System::System(std::initializer_list<ComponentManagerBase*> c)
{
    // TODO see if we can listen ot entityAdded and entityDeleted
    // event ot maintain the entities list instead of updating
    // it on demand
    Debug::printl("CONSTRUCTOR 3");
    for (auto componentManager : c) {
        componentManagers.push_back(componentManager);
    }
}

void System::update(float /*time*/)
{
    Debug::printl("Warning: update(time) function called but not implemented by System");
}

void System::update()
{
    Debug::printl("Warning: update() function called but not implemented by System");
}

std::vector<id>* System::getEntities()
{
    // TODO put that in a function
    unsigned int newTotalEntities {0};
    for (auto componentManager : componentManagers) {
        newTotalEntities += componentManager->getEntities()->size();
    }

    if (newTotalEntities != totalEntities) {
        totalEntities = newTotalEntities;

        // TODO put that in a function
        entities.reserve(totalEntities);
        for (auto componentManager : componentManagers) {
            copy(componentManager->getEntities()->begin(), componentManager->getEntities()->end(), back_inserter(entities));
        }
        sort(entities.begin(), entities.end());
        entities.erase(unique(entities.begin(), entities.end() ), entities.end());
    }

    return &entities;
}
}
