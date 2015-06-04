#pragma once
#include "ecs/System.hpp"
#include "components/Movement.hpp"

namespace ECS {
    template <typename T> class ComponentManager;
}

class MovementSystem : public ECS::System
{

public:

    MovementSystem(
        ECS::ComponentManager<Movement>* mc
    );

    void update(float seconds, float delta) override;

private:

    ECS::ComponentManager<Movement>* movementComponents;
};

