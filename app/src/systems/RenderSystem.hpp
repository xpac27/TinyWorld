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

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Position>* positionComponents;
};
