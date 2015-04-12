#pragma once
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "ecs/System.hpp"
#include "ecs/ComponentManager.hpp"
#include "components/Visibility.hpp"
#include "components/Position.hpp"
#include "math/Vertex.hpp"
#include "math/Triangle.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class RenderSystem : public ECS::System {

public:

    RenderSystem(
        ECS::ComponentManager<Visibility>* vc,
        ECS::ComponentManager<Position>* pc
    )
        : System({vc, pc})
        , visibilityComponents(vc)
        , positionComponents(pc)
    {}

    void initialize();
    void update();

private:

    // TODO save those shapes into classes and set a shape property in the visibility component
    Vertex vertices[4];
    Triangle triangles[2];
    GLubyte indexes[6];
    GLuint VBOIds[2];
    GLsizei totalIndexes = 6;
    unsigned int totalVertex = 4;

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Position>* positionComponents;
};
