#pragma once
#include <vector>

#include "ecs/Component.hpp"

namespace ECS
{

class System
{
public:
    System(unsigned int mask) : componentTypes(mask) {}

    void registerEntity(unsigned int entity);
    void unregisterEntity(unsigned int entity);

    bool useComponent(unsigned int mask) const;

    template <typename C, typename... Components>
    void requires()
    {
        requires<C>();
        requires<Components...>();
    }

    template <typename C>
    void requires()
    {
    }

protected:
    unsigned int componentTypes;

private:
    std::vector<unsigned int> entities;
};

}
