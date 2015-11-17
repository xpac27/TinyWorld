#pragma once
#include "ecs/System.hpp"
#include "components/Visibility.hpp"
#include "components/Movement.hpp"
#include "graphic/Model.hpp"
#include "utils/Aggregator.hpp"
#include <glm/vec3.hpp>

class Renderer;
namespace ECS {
template <typename T> class ComponentManager;
}

class RenderSystem : public ECS::System
{

public:

    RenderSystem(
        ECS::ComponentManager<Visibility>* vc,
        ECS::ComponentManager<Movement>* mc
    );
    ~RenderSystem();

    void initialize() override;
    void update() override;

private:

    float count = 0.f;

    Aggregator<Model> models;

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Movement>* movementComponents;

    // TODO init from outside (systems class?)
    Renderer *renderer;
};
