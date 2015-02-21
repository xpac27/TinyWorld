#pragma once
#include <vector>
#include <climits>
#include <assert.h>
#include "Component.hpp"
#include "System.hpp"

#define mask(n) ((1) << (n))

class EntitiesManager
{
    public:
        unsigned int addEntity();
        unsigned int getEntityCount() const;

        void resetEntity(unsigned int entity);

        template<class T>
            void registerComponent();
        template<class T>
            void registerSystem();
        template<class T>
            void delComponent(unsigned int entity);
        template<class T>
            bool hasComponent(unsigned int entity) const;
        template<class T>
            T* addComponent(unsigned int entity);
        template<class T>
            T* getComponent(unsigned int entity) const;

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
    for (auto i : entitiesComponentsIndex) i.push_back(UINT_MAX);
}

template<class T>
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
    entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex) = unsigned(Component<T>::list.size());
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

template<class T>
void EntitiesManager::delComponent(unsigned int entity)
{
    assert(entitiesComponentsIndex.size() > entity);
    assert(entitiesComponentsIndex.at(entity).size() > Component<T>::typeIndex);
    entitiesComponentsIndex.at(entity).at(Component<T>::typeIndex) = UINT_MAX;
    for (auto s : systems) if (s.useComponent(mask(Component<T>::typeIndex))) s.unregisterEntity(entity);
}
