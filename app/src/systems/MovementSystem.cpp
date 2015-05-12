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

void MovementSystem::update(double /*milliseconds*/, float delta)
{
    ECS::id entity;
    Movement* movement;

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        entity = getEntities()->at(i);

        movement = movementComponents->getComponent(entity);
        movement->position += movement->direction * delta * movement->velocity;
    }
}
