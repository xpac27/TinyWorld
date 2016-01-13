#pragma once

#include <ecs/EntityManager.hpp>
#include <ecs/SystemManager.hpp>
#include <ecs/ComponentManager.hpp>

#include <components/Life.hpp>
#include <components/Movement.hpp>
#include <components/Visibility.hpp>

class Game
{
public:

    Game();

    void draw();
    void printStats();
    void update(float seconds);
    void reload();

private:

    void setupWorld();
    void addEntity();
    void addTestEntity();

    ecs::EntityManager entities = {};

    ecs::SystemManager visualSystems;
    ecs::SystemManager simulationSystems;

    ecs::ComponentManager<Life> lifeComponents = ecs::ComponentManager<Life>();
    ecs::ComponentManager<Movement> movementComponents = ecs::ComponentManager<Movement>();
    ecs::ComponentManager<Visibility> visibilityComponents = ecs::ComponentManager<Visibility>();
};
