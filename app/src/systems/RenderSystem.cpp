#include "RenderSystem.hpp"
#include "ecs/ComponentManager.hpp"
#include "graphic/Vertex.hpp"
#include "graphic/MeshFactory.hpp"
#include "graphic/Mesh.hpp"
#include "ecs/Id.hpp"

RenderSystem::RenderSystem(
    ECS::ComponentManager<Visibility>* vc,
    ECS::ComponentManager<Position>* pc
)
    : System({vc, pc})
    , meshFactory(new MeshFactory())
    , visibilityComponents(vc)
    , positionComponents(pc)
{}

void RenderSystem::initialize()
{
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (GLvoid*)(sizeof(float)*3));
    glNormalPointer(GL_FLOAT, sizeof(Vertex), (GLvoid*)(sizeof(float)*5));
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), (GLvoid*)(sizeof(float)*8));

}

void RenderSystem::update()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_COLOR_MATERIAL); // TODO avoid

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);

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

            meshFactory->getMesh(visibility->meshType)->draw();

            glPopMatrix();
        }
    }

    // TODO use push states
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
}
