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
    if (GLEW_ARB_vertex_buffer_object)
    {
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
        glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (GLvoid*)(sizeof(float)*3));
        glNormalPointer(GL_FLOAT, sizeof(Vertex), (GLvoid*)(sizeof(float)*5));
        glColorPointer(4, GL_FLOAT, sizeof(Vertex), (GLvoid*)(sizeof(float)*8));
    }
}

void RenderSystem::update()
{
    ECS::id entity;
    Position* position;
    Visibility* visibility;

    setGLStates();
    glPushMatrix();
    glTranslatef(0.f, 0.f, -30.f);

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

    glPopMatrix();
    unsetGLStates();
}

void RenderSystem::setGLStates()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.8f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.004f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.00005f);

    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (GLEW_ARB_vertex_buffer_object)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
    }
}

void RenderSystem::unsetGLStates()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
}
