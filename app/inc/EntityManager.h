#pragma once
#include <vector>
#include <climits>
#include <assert.h>
#include "Component.h"
#include "System.h"

#define mask(n) ((1) << (n))

class System;
class EntitiesManager
{
    public:
        unsigned int addEntity();
        unsigned int getEntityCount() const;

        void resetEntity(unsigned int entity);

        template<typename T>
            void registerComponent();
        template<typename T>
            void registerSystem();
        template<typename T>
            void delComponent(unsigned int entity);
        template<typename T>
            bool hasComponent(unsigned int entity) const;
        template<typename T>
            T* addComponent(unsigned int entity);
        template<typename T>
            T* getComponent(unsigned int entity) const;

    private:
        unsigned int entityCount = 0;
        unsigned int componentTypeCount = 0;

        std::vector<System> systems;
        std::vector<std::vector<unsigned int>> entitiesComponentsIndex;
};
