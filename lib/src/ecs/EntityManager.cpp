#include "../../inc/ecs/EntityManager.hpp"

namespace ecs {

id EntityManager::addEntity()
{
    return ++totalEntities - 1;
}

unsigned int EntityManager::getTotal()
{
    return totalEntities;
}

}
