#pragma once
#include <vector>

#include "ecs/Component.hpp"

namespace ECS
{

class System
{
public:
    System(unsigned int mask) : componentTypes(mask) {}

    void update(float time);

    void registerEntity(unsigned int entity);
    void unregisterEntity(unsigned int entity);

    bool useComponent(unsigned int mask) const;

protected:
    unsigned int componentTypes;

private:
    std::vector<unsigned int> entities;
};

}
