#pragma once
#include <ecs/System.hpp>
#include <components/Visibility.hpp>
#include <components/Movement.hpp>
#include <glm/glm.hpp>

class Renderer;
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

    void update(Renderer& renderer);

private:

    float count = 0.f;

    ecs::ComponentManager<Visibility>* visibilityComponents;
    ecs::ComponentManager<Movement>* movementComponents;
};
