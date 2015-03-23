#include "ComponentManagerBase.hpp"

namespace ECS {

std::vector<id>* ComponentManagerBase::getEntities()
{
    return &entities;
}

void ComponentManagerBase::addEntity(id entity)
{
    entities.push_back(entity);
}

void ComponentManagerBase::delEntity(id /*entity*/)
{
    // TODO
    // entities.erase(entities at entity);
}
}
