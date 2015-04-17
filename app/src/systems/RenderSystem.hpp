#pragma once
#include "ecs/System.hpp"
#include "ecs/ComponentManager.hpp"
#include "components/Visibility.hpp"
#include "components/Position.hpp"
#include "graphic/MeshFactory.hpp"

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

    void update();

private:

    MeshFactory meshFactory;

    float ca = 0.5f;
    float la = 0.004f;
    float qa = 0.00005f;

    GLfloat lightPos[4] {0.f, 0.f, 10.f, 1.f};
    GLfloat lightAmb[4] {.5f, .5f, .5f, 0.f};
    GLfloat lightDif[4] {.5f, .5f, .5f, 1.f};

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Position>* positionComponents;
};
