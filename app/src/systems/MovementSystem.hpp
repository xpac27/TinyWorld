#pragma once
#include "ecs/System.hpp"
#include "components/Position.hpp"
#include "components/Physics.hpp"

namespace ECS {
    template <typename T> class ComponentManager;
}
class MovementSystem : public ECS::System {

public:

    MovementSystem(
        ECS::ComponentManager<Position>* pc,
        ECS::ComponentManager<Physics>* ppc
    );

    void update(float time);

private:

    ECS::ComponentManager<Position>* positionComponents;
    ECS::ComponentManager<Physics>* physicsComponents;
};

