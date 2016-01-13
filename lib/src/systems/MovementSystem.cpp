#include "../../inc/systems/MovementSystem.hpp"
#include "../../inc/ecs/ComponentManager.hpp"
#include "../../inc/ecs/Id.hpp"
#include "../utils/log.hpp"
#include <math.h>

using namespace ecs;

MovementSystem::MovementSystem(
    ComponentManager<Movement>* mc
)
    : System({mc})
    , movementComponents(mc)
{}

void MovementSystem::update(float /*seconds*/, float delta)
{
    id entity;
    Movement* movement;

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        entity = getEntities()->at(i);

        movement = movementComponents->getComponent(entity);
        movement->position += movement->direction * delta * movement->velocity;
    }
}
