#pragma once
#include <vector>
#include "Entity.hpp"

namespace ECS {

class ComponentManagerBase
{

public:

    std::vector<id>* getEntities();

protected:

    void addEntity(id entity);
    void delEntity(id entity);

private:

    std::vector<id> entities;
};
}
