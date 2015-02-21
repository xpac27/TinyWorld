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

template<class T>
void EntitiesManager::registerSystem()
{
    systems.push_back(T());
}

template<class T>
void EntitiesManager::registerComponent()
{
    Component<T>::typeIndex = componentTypeCount;
    componentTypeCount ++;
    for (auto i : entitiesComponentsIndex) i.push_back(UINT_MAX);
}

template<typename T>
bool EntitiesManager::hasComponent(unsigned int entity) const 
{
    assert(entitiesComponentsIndex.size() > entity);
    assert(entitiesComponentsIndex.at(entity).size() > Component<T>::typeIndex);
    return entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex) != UINT_MAX;
}

// TODO return the first available component
template<class T>
T* EntitiesManager::addComponent(unsigned int entity) {
    assert(entitiesComponentsIndex.size() > entity);
    assert(entitiesComponentsIndex.at(entity).size() > Component<T>::typeIndex);
    entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex) = Component<T>::list.size();
    Component<T>::list.push_back(T());
    for (auto s : systems) if (s.useComponent(mask(Component<T>::typeIndex))) s.registerEntity(entity);
    return &Component<T>::list.back();
}

template<class T>
T* EntitiesManager::getComponent(unsigned int entity) const {
    assert(entitiesComponentsIndex.size() > entity);
    assert(entitiesComponentsIndex.at(entity).size() > Component<T>::typeIndex);
    assert(Component<T>::list.size() > entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex));
    return &Component<T>::list.at(entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex));
}

template<typename T>
void EntitiesManager::delComponent(unsigned int entity)
{
    assert(entitiesComponentsIndex.size() > entity);
    assert(entitiesComponentsIndex.at(entity).size() > Component<T>::typeIndex);
    entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex) = UINT_MAX;
    for (auto s : systems) if (s.useComponent(mask(Component<T>::typeIndex))) s.unregisterEntity(entity);
}
