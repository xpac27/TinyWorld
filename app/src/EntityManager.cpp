#include "EntityManager.hpp"

Index EntitiesManager::getEntityCount() const
{
    return entityCount;
}

// TODO return the first available entity
Index EntitiesManager::addEntity()
{
    if (entityAvailable()) {
        entitiesComponentsIndex.push_back(std::vector<Index>(componentTypeCount));
        std::fill(entitiesComponentsIndex.back().begin(), entitiesComponentsIndex.back().end(), UINT_MAX);
        entityCount ++;
    }
    return entityCount - 1;
}

void EntitiesManager::resetEntity(Index entity)
{
    if (hasEntity(entity)) {
        std::fill(entitiesComponentsIndex.at(entity).begin(), entitiesComponentsIndex.at(entity).end(), UINT_MAX);
    }
}

void EntitiesManager::addSystem(System system)
{
    systems.push_back(system);
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

void EntitiesManager::extendIndexCapacity()
{
    for (auto& i : entitiesComponentsIndex) {
        i.push_back(UINT_MAX);
    }
}

bool EntitiesManager::entityAvailable()
{
    if (entityCount < UINT_MAX) {
        return true;
    } else {
        throw std::out_of_range("You've reach the maximum number of entities!");
    }
}

bool EntitiesManager::hasEntity(Index entity)
{
    if (entitiesComponentsIndex.size() > entity) {
        return true;
    } else {
        throw std::invalid_argument("Entity index doesn't exist");
    }
}

bool EntitiesManager::hasComponent(Index entity, Index index)
{
    if (hasEntity(entity) && entitiesComponentsIndex.at(entity).at(index) != UINT_MAX) {
        return true;
    } else {
        throw std::invalid_argument("Entity doesn't have this component");
    }
}

bool EntitiesManager::hasNoComponent(Index entity, Index index)
{
    if (hasEntity(entity) && entitiesComponentsIndex.at(entity).at(index) == UINT_MAX) {
        return true;
    } else {
        throw std::invalid_argument("Entity already has this component");
    }
}
