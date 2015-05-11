#include "MovementSystem.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/Id.hpp"
#include "utils/Log.hpp"
#include <math.h>

MovementSystem::MovementSystem(
    ECS::ComponentManager<Movement>* mc
)
    : System({mc})
    , movementComponents(mc)
{}

void MovementSystem::update(long /*milliseconds*/, long delta)
{
    ECS::id entity;
    Movement* movement;

    Log::printl((float(delta) / 1000.f));

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        entity = getEntities()->at(i);

        movement = movementComponents->getComponent(entity);
        movement->position += movement->direction * 0.051f;
        // TODO implement movement...

        Log::printl(movement->position.x, movement->position.y, movement->position.z);
    }
}
