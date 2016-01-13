#pragma once
#include <ecs/System.hpp>
#include <components/Visibility.hpp>
#include <components/Movement.hpp>
#include <glm/vec3.hpp>

class Renderer;
class Model;
template <typename T> class Aggregator;
namespace ecs {
template <typename T> class ComponentManager;
}

class RenderSystem : public ecs::System
{

public:

    RenderSystem(
        ecs::ComponentManager<Visibility>* vc,
        ecs::ComponentManager<Movement>* mc
    );
    ~RenderSystem();

    void initialize() override;
    void reload() override;
    void update() override;

private:

    float count = 0.f;

    ecs::ComponentManager<Visibility>* visibilityComponents;
    ecs::ComponentManager<Movement>* movementComponents;

    Aggregator<Model>* models;

    // TODO init from outside (systems class?)
    Renderer *renderer;
};
