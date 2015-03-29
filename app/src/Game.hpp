#pragma once

#include "ecs/EntityManager.hpp"
#include "ecs/SystemManager.hpp"
#include "ecs/ComponentManager.hpp"

#include "components/Life.hpp"
#include "components/Position.hpp"
#include "components/Visibility.hpp"
#include "components/Physics.hpp"

class Game
{
public:

    Game();

    void update(float time);
    void draw();

private:

    void addEntity();

    ECS::EntityManager entities = {};

    ECS::SystemManager visualSystems = {};
    ECS::SystemManager simulationSystems = {};

    ECS::ComponentManager<Life> lifeComponents = ECS::ComponentManager<Life>();
    ECS::ComponentManager<Position> positionComponents = ECS::ComponentManager<Position>();
    ECS::ComponentManager<Visibility> visibilityComponents = ECS::ComponentManager<Visibility>();
    ECS::ComponentManager<Physics> physicsComponents = ECS::ComponentManager<Physics>();
};
