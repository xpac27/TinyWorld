#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "ecs/Entity.hpp"
#include "RenderSystem.hpp"
#include "helpers/Debug.hpp"

void RenderSystem::update()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);

    glBlendFunc(GL_ONE, GL_ONE);
    glDepthFunc(GL_LEQUAL);

    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ECS::id entity;
    Position* position;
    Visibility* visibility;

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        entity = getEntities()->at(i);

        if (visibilityComponents->hasComponent(entity)) {
            visibility = visibilityComponents->getComponent(entity);

            if (visibility->active) {

                glPushMatrix();

                if (positionComponents->hasComponent(entity)) {
                    position = positionComponents->getComponent(entity);
                    glTranslatef(position->x, position->y, 0.f);
                }

                glBegin(GL_TRIANGLES);
                glColor4f(1.f, 1.f, 0.f, 0.6f);
                glVertex3f(0.f, 0.f, 0.f);
                glVertex3f(1.f, 1.f, 0.f);
                glVertex3f(0.f, 1.f, 0.f);
                glVertex3f(0.f, 0.f, 0.f);
                glVertex3f(1.f, 0.f, 0.f);
                glVertex3f(1.f, 1.f, 0.f);
                glEnd();

                glPopMatrix();
            }
        }
    }
}
