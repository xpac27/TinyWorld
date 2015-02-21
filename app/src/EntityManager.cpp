#include "EntityManager.h"

// TODO return the first available entity
unsigned int EntitiesManager::addEntity()
{
    assert(entityCount < UINT_MAX);
    entitiesComponentsIndex.push_back(std::vector<unsigned int>(componentTypeCount));
    std::fill(entitiesComponentsIndex.back().begin(), entitiesComponentsIndex.back().end(), UINT_MAX);
    return ++entityCount - 1;
}

unsigned int EntitiesManager::getEntityCount() const
{
    return entityCount;
}

void EntitiesManager::resetEntity(unsigned int entity)
{
    assert(entitiesComponentsIndex.size() > entity);
    std::fill(entitiesComponentsIndex.at(entity).begin(), entitiesComponentsIndex.at(entity).end(), UINT_MAX);
}
