#pragma once
#include <vector>
#include <initializer_list>
#include "ComponentManagerBase.hpp"

namespace ECS {
typedef unsigned long id;

class System
{

public:

    System(std::initializer_list<ComponentManagerBase*> c);

    virtual ~System() = default;

    virtual void update();
    virtual void update(float time);

protected:

    std::vector<id>* getEntities();

private:

    unsigned int totalEntities {0};

    std::vector<id> entities;
    std::vector<ComponentManagerBase*> componentManagers = {};
};
}
