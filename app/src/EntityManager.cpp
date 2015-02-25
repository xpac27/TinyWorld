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
