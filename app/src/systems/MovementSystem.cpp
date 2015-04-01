#include "ecs/Id.hpp"
#include "RenderSystem.hpp"
#include "helpers/Debug.hpp"
#include "systems/MovementSystem.hpp"
#include <math.h>

void MovementSystem::update()
{
    ECS::id entity;
    Position* position;
    Physics* physics;

    count += 0.02;
    double ratio = sin(count);

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        entity = getEntities()->at(i);

        if (positionComponents->hasComponent(entity) && physicsComponents->hasComponent(entity)) {
            position = positionComponents->getComponent(entity);
            physics = physicsComponents->getComponent(entity);

            position->x += physics->velocity_x * ratio;
            position->y += physics->velocity_y * ratio;
        }
    }
}

