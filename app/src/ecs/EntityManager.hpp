#pragma once
#include <vector> // fix

namespace ECS {
typedef size_t id;

class EntityManager
{
public:

    id addEntity();

    unsigned int getTotal();

private:

    unsigned int totalEntities = 0;
};

}
