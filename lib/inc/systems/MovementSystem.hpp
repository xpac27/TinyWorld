#pragma once
#include <ecs/System.hpp>
#include <components/Movement.hpp>

namespace ecs {
    template <typename T> class ComponentManager;
}

class MovementSystem : public ecs::System
{

public:

    MovementSystem(
        ecs::ComponentManager<Movement>* mc
    );

    void update(float seconds, float delta) override;

private:

    ecs::ComponentManager<Movement>* movementComponents;
};

