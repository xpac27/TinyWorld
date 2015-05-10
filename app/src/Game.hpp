#pragma once

#include "ecs/EntityManager.hpp"
#include "ecs/SystemManager.hpp"
#include "ecs/ComponentManager.hpp"

#include "components/Life.hpp"
#include "components/Movement.hpp"
#include "components/Visibility.hpp"

class Game
{
public:

    Game();

    void draw();
    void printStats();
    void update(long milliseconds);

private:

    void addEntity();

    ECS::EntityManager entities = {};

    ECS::SystemManager visualSystems = ECS::SystemManager("VIS");
    ECS::SystemManager simulationSystems = ECS::SystemManager("SIM");

    ECS::ComponentManager<Life> lifeComponents = ECS::ComponentManager<Life>();
    ECS::ComponentManager<Movement> movementComponents = ECS::ComponentManager<Movement>();
    ECS::ComponentManager<Visibility> visibilityComponents = ECS::ComponentManager<Visibility>();
};
