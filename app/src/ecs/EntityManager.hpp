#pragma once

namespace ECS {
typedef unsigned long id;

class EntityManager
{
public:

    id addEntity();

    unsigned int getTotal();

private:

    unsigned int totalEntities = 0;
};

}
