#pragma once
#include <ecs/Id.hpp>

namespace ecs {
class EntityManager
{
public:

    id addEntity();

    unsigned int getTotal();

private:

    unsigned int totalEntities = 0;
};
}
