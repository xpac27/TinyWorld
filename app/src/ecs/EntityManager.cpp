#include "ecs/EntityManager.hpp"

ECS::Index ECS::EntitiesManager::getEntityCount() const
{
    return entityCount;
}

// TODO return the first available entity
ECS::Index ECS::EntitiesManager::addEntity()
{
    if (entityAvailable()) {
        entitiesComponentsIndex.push_back(std::vector<ECS::Index>(mapper.getTotal()));
        std::fill(entitiesComponentsIndex.back().begin(), entitiesComponentsIndex.back().end(), UINT_MAX);
        entityCount ++;
    }
    return entityCount - 1;
}

void ECS::EntitiesManager::resetEntity(ECS::Index entity)
{
    if (hasEntity(entity)) {
        std::fill(entitiesComponentsIndex.at(entity).begin(), entitiesComponentsIndex.at(entity).end(), UINT_MAX);
    }
}

void ECS::EntitiesManager::addSystem(System* system)
{
    systems.push_back(system);
}

void ECS::EntitiesManager::registerEntity(ECS::Index entity, ECS::Index index)
{
    for (auto s : systems) {
        if (s->useComponent(index)) {
            s->registerEntity(entity);
        }
    }
}

void ECS::EntitiesManager::unregisterEntity(ECS::Index entity, ECS::Index index)
{
    for (auto s : systems) {
        if (s->useComponent(index)) {
            s->unregisterEntity(entity);
        }
    }
}

void ECS::EntitiesManager::extendIndexCapacity()
{
    for (auto& i : entitiesComponentsIndex) {
        i.push_back(UINT_MAX);
    }
}

bool ECS::EntitiesManager::entityAvailable()
{
    if (entityCount < UINT_MAX) {
        return true;
    } else {
        throw std::out_of_range("You've reach the maximum number of entities!");
    }
}

bool ECS::EntitiesManager::hasEntity(ECS::Index entity)
{
    if (entitiesComponentsIndex.size() > entity) {
        return true;
    } else {
        throw std::invalid_argument("Entity index doesn't exist");
    }
}

bool ECS::EntitiesManager::hasComponent(ECS::Index entity, ECS::Index index)
{
    if (hasEntity(entity) && entitiesComponentsIndex.at(entity).at(index) != UINT_MAX) {
        return true;
    } else {
        throw std::invalid_argument("Entity doesn't have this component");
    }
}

bool ECS::EntitiesManager::hasNoComponent(ECS::Index entity, ECS::Index index)
{
    if (hasEntity(entity) && entitiesComponentsIndex.at(entity).at(index) == UINT_MAX) {
        return true;
    } else {
        throw std::invalid_argument("Entity already has this component");
    }
}
