#pragma once
#include "ecs/Id.hpp"
#include "utils/Signal.hpp"

namespace ECS {
class System;

class ComponentManagerBase
{

public:

    Signal<System, id>* getEntityAddedSignal();
    Signal<System, id>* getEntityRemovedSignal();

protected:

    void fireEntityAddedSignal(id entity);
    void fireEntityRemovedSignal(id entity);

private:

    Signal<System, id> entityAddedSignal {};
    Signal<System, id> entityRemovedSignal {};
};
}
