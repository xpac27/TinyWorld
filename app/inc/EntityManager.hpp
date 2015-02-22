#pragma once
#include <vector>
#include <climits>
#include <assert.h>
#include "Component.hpp"
#include "System.hpp"

#define mask(n) ((1) << (n))

typedef unsigned int Entity;

class EntitiesManager
{
    public:
        Entity addEntity();
        Entity getEntityCount() const;

        void resetEntity(Entity entity);

        template<class T>
            void registerComponent();
        template<class T>
            void registerSystem();
        template<class T>
            void delComponent(Entity entity);
        template<class T>
            bool hasComponent(Entity entity) const;
        template<class T>
            T* addComponent(Entity entity);
        template<class T>
            T* getComponent(Entity entity) const;

    private:
        unsigned int entityCount = 0;
        unsigned int componentTypeCount = 0;

        std::vector<System> systems;
        std::vector<std::vector<unsigned int>> entitiesComponentsIndex;
};

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
    for (auto & i : entitiesComponentsIndex) i.push_back(UINT_MAX);
}

template<class T>
bool EntitiesManager::hasComponent(Entity entity) const
{
    if (entitiesComponentsIndex.size() < entity)
        throw std::logic_error("Entity index doesn't exist");
    if (entitiesComponentsIndex.at(entity).size() < Component<T>::typeIndex)
        throw std::logic_error("Component has not been registered");

    return entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex) != UINT_MAX;
}

// TODO return the first available component
template<class T>
T* EntitiesManager::addComponent(Entity entity)
{
    if (entitiesComponentsIndex.size() < entity)
        throw std::logic_error("Entity index doesn't exist");
    if (entitiesComponentsIndex.at(entity).size() < Component<T>::typeIndex)
        throw std::logic_error("Component has not been registered");
    if (entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex) != UINT_MAX)
        throw std::logic_error("Entity already has this component");

    entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex) = unsigned(Component<T>::list.size());
    Component<T>::list.push_back(T());
    for (auto s : systems) if (s.useComponent(mask(Component<T>::typeIndex))) s.registerEntity(entity);
    return &Component<T>::list.back();
}

template<class T>
T* EntitiesManager::getComponent(Entity entity) const
{
    assert(entitiesComponentsIndex.size() > entity);
    assert(entitiesComponentsIndex.at(entity).size() > Component<T>::typeIndex);
    assert(Component<T>::list.size() > entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex));
    return &Component<T>::list.at(entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex));
}

template<class T>
void EntitiesManager::delComponent(Entity entity)
{
    assert(entitiesComponentsIndex.size() > entity);
    assert(entitiesComponentsIndex.at(entity).size() > Component<T>::typeIndex);
    entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex) = UINT_MAX;
    for (auto s : systems) if (s.useComponent(mask(Component<T>::typeIndex))) s.unregisterEntity(entity);
}
