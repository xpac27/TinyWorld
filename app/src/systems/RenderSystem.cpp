#include <SFML/OpenGL.hpp>
#include "ecs/Id.hpp"
#include "RenderSystem.hpp"
#include "helpers/Debug.hpp"

void RenderSystem::update()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT);

    ECS::id entity;
    Position* position;
    Visibility* visibility;

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        entity = getEntities()->at(i);

        if (visibilityComponents->hasComponent(entity)) {
            visibility = visibilityComponents->getComponent(entity);

            glPushMatrix();

            if (positionComponents->hasComponent(entity)) {
                position = positionComponents->getComponent(entity);
                glTranslatef(position->x, position->y, 0.f);
            }

            meshFactory.getMesh(visibility->meshType)->draw();

            glPopMatrix();
        }
    }
}
