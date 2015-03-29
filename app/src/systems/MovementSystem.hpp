#pragma once
#include "ecs/System.hpp"
#include "ecs/ComponentManager.hpp"
#include "components/Position.hpp"
#include "components/Physics.hpp"

class MovementSystem : public ECS::System {

public:

    MovementSystem(
        ECS::ComponentManager<Position>* pc,
        ECS::ComponentManager<Physics>* ppc
    )
        : System({pc, ppc})
        , positionComponents(pc)
        , physicsComponents(ppc)
    {}

    void update();

private:

    ECS::ComponentManager<Position>* positionComponents;
    ECS::ComponentManager<Physics>* physicsComponents;
};

