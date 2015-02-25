#include "EntityManager.hpp"

Index EntitiesManager::getEntityCount() const
{
    return entityCount;
}

void EntitiesManager::resetEntity(Index entity)
{
    if (entitiesComponentsIndex.size() <= entity) {
        throw std::invalid_argument("Entity index doesn't exist");
    } else {
        std::fill(entitiesComponentsIndex.at(entity).begin(), entitiesComponentsIndex.at(entity).end(), UINT_MAX);
    }
}

// TODO return the first available entity
Index EntitiesManager::addEntity()
{
    if (entityCount >= UINT_MAX) {
        throw std::out_of_range("You've reach the maximum number of entities!");
    } else {
        entitiesComponentsIndex.push_back(std::vector<Index>(componentTypeCount));
        std::fill(entitiesComponentsIndex.back().begin(), entitiesComponentsIndex.back().end(), UINT_MAX);
        return ++entityCount - 1;
    }
}

void EntitiesManager::extendIndexCapacity()
{
    for (auto& i : entitiesComponentsIndex) {
        i.push_back(UINT_MAX);
    }
}

bool EntitiesManager::hasEntity(Index entity)
{
    return entitiesComponentsIndex.size() > entity;
}

void EntitiesManager::registerEntity(Index entity, Index index)
{
    for (auto s : systems) {
        if (s.useComponent(index)) {
            s.registerEntity(entity);
        }
    }
}

void EntitiesManager::unregisterEntity(Index entity, Index index)
{
    for (auto s : systems) {
        if (s.useComponent(index)) {
            s.unregisterEntity(entity);
        }
    }
}

void EntitiesManager::addSystem(System system)
{
    systems.push_back(system);
}
