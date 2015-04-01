#pragma once
#include "Id.hpp"

namespace ECS {

class EntityManager
{
public:

    id addEntity();

    unsigned int getTotal();

private:

    unsigned int totalEntities = 0;
};
}
