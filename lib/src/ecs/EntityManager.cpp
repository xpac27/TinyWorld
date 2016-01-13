#include "../../inc/ecs/EntityManager.hpp"

namespace ECS {

id EntityManager::addEntity()
{
    return ++totalEntities - 1;
}

unsigned int EntityManager::getTotal()
{
    return totalEntities;
}

}
