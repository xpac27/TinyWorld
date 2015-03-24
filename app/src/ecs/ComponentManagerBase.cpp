#include "ComponentManagerBase.hpp"

namespace ECS {

Signal<System, id>* ComponentManagerBase::getEntityAddedSignal()
{
    return &entityAddedSignal;
}

Signal<System, id>* ComponentManagerBase::getEntityRemovedSignal()
{
    return &entityRemovedSignal;
}

void ComponentManagerBase::fireEntityAddedSignal(id entity)
{
    entityAddedSignal.fire(entity);
}

void ComponentManagerBase::fireEntityRemovedSignal(id entity)
{
    entityRemovedSignal.fire(entity);
}
}
