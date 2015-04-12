#include "ecs/Id.hpp"
#include "RenderSystem.hpp"
#include "helpers/Debug.hpp"

void RenderSystem::initialize()
{
    vertices[0].pos[0] = -1.f;
    vertices[0].pos[1] =  1.f;
    vertices[0].pos[2] =  0.f;

    vertices[1].pos[0] =  1.f;
    vertices[1].pos[1] =  1.f;
    vertices[1].pos[2] =  0.f;

    vertices[2].pos[0] =  1.f;
    vertices[2].pos[1] = -1.f;
    vertices[2].pos[2] =  0.f;

    vertices[3].pos[0] = -1.f;
    vertices[3].pos[1] = -1.f;
    vertices[3].pos[2] =  0.f;

    triangles[0].vi[0] = indexes[0] = 0;
    triangles[0].vi[1] = indexes[1] = 1;
    triangles[0].vi[2] = indexes[2] = 2;

    triangles[1].vi[0] = indexes[3] = 2;
    triangles[1].vi[1] = indexes[4] = 3;
    triangles[1].vi[2] = indexes[5] = 0;

    for (unsigned int i = 0; i < totalVertex; i++)
    {
        vertices[i].col[0] = 1.f;
        vertices[i].col[1] = 1.f;
        vertices[i].col[2] = 0.f;
        vertices[i].col[3] = 0.2f;
    }

    glGenBuffers(2, VBOIds);

    glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * totalVertex, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * unsigned(totalIndexes), indexes, GL_STATIC_DRAW);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (GLvoid*)(sizeof(float)*3));
    glNormalPointer(GL_FLOAT, sizeof(Vertex), (GLvoid*)(sizeof(float)*5));
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), (GLvoid*)(sizeof(float)*8));
}

void RenderSystem::update()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBOIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIds[1]);

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

                glDrawElements(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_BYTE, NULL);

                glPopMatrix();
            }
        }
    }
}
