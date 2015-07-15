#pragma once
#include "ecs/Id.hpp"
#include <vector>
#include <initializer_list>

namespace ECS {
class ComponentManagerBase;
class System
{

public:

    System(std::initializer_list<ComponentManagerBase*> c);

    virtual ~System() = default;

    virtual void initialize();
    virtual void update();
    virtual void update(float seconds, float delta);

    std::vector<id>* getEntities();

protected:

    virtual void entityAdded(id entity);
    virtual void entityRemoved(id entity);

private:

    void onEntityAdded(id entity);
    void onEntityRemoved(id entity);

    std::vector<id> entities {};
    std::vector<ComponentManagerBase*> componentManagers {};
};
}
