#include "../../inc/ecs/ComponentManagerBase.hpp"
#include "../utils/Signal.hpp"

namespace ECS {

ComponentManagerBase::ComponentManagerBase()
    : entityAddedSignal(new Signal<System, id>())
    , entityRemovedSignal(new Signal<System, id>())
{
}

Signal<System, id>* ComponentManagerBase::getEntityAddedSignal()
{
    return entityAddedSignal;
}

Signal<System, id>* ComponentManagerBase::getEntityRemovedSignal()
{
    return entityRemovedSignal;
}

void ComponentManagerBase::fireEntityAddedSignal(id entity)
{
    entityAddedSignal->fire(entity);
}

void ComponentManagerBase::fireEntityRemovedSignal(id entity)
{
    entityRemovedSignal->fire(entity);
}
}
