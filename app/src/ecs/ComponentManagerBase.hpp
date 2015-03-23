#pragma once
#include <vector>

namespace ECS {
typedef unsigned long id;

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
