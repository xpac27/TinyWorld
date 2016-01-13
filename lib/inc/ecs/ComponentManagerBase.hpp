#pragma once
#include <ecs/Id.hpp>

template<typename C, typename T>
class Signal;

namespace ECS {
class System;

class ComponentManagerBase
{

public:

    ComponentManagerBase();

    Signal<System, id>* getEntityAddedSignal();
    Signal<System, id>* getEntityRemovedSignal();

protected:

    void fireEntityAddedSignal(id entity);
    void fireEntityRemovedSignal(id entity);

private:

    Signal<System, id>* entityAddedSignal {};
    Signal<System, id>* entityRemovedSignal {};
};
}
