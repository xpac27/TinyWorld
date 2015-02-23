#pragma once
#include <vector>
#include "Component.hpp"
#define mask(n) ((1) << (n))

class System
{
public:
    System(unsigned int mask) : componentTypes(mask) {}

    void registerEntity(unsigned int entity);
    void unregisterEntity(unsigned int entity);

    bool useComponent(unsigned int mask) const;

    template <typename T>
    bool useComponent() const;

protected:
    unsigned int componentTypes;

private:
    std::vector<unsigned int> entities;
};
