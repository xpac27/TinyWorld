#pragma once
#include <ecs/System.hpp>
#include <components/Visibility.hpp>
#include <components/Movement.hpp>
#include <glm/vec3.hpp>

class Renderer;
class Model;
template <typename T> class Aggregator;
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
    void reload() override;
    void update() override;

private:

    float count = 0.f;

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Movement>* movementComponents;

    Aggregator<Model>* models;

    // TODO init from outside (systems class?)
    Renderer *renderer;
};
