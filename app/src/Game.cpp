#include "Game.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "utils/Random.hpp"
#include <glm/detail/func_geometric.hpp>

Game::Game()
    : visualSystems("VIS")
    , simulationSystems("SIM")
{
    visualSystems.addRenderSystem(&visibilityComponents, &movementComponents);
    visualSystems.initialize();

    simulationSystems.addMovementSystem(&movementComponents);
    simulationSystems.setLatency(1.f / 100.f);
    simulationSystems.initialize();

    for (int i = 0; i < 100; i ++) {
        addEntity();
    }
}

void Game::draw()
{
    visualSystems.update();
}

void Game::printStats()
{
    visualSystems.printStats();
    simulationSystems.printStats();
}

void Game::update(float seconds)
{
    simulationSystems.update(seconds);
}

void Game::addEntity()
{
    ECS::id entity = entities.addEntity();
    movementComponents.addComponent(entity);
    visibilityComponents.addComponent(entity);
    movementComponents.getComponent(entity)->velocity = Random::get(2.f, 5.f);
    movementComponents.getComponent(entity)->direction = {Random::get(-1.f, 1.f), Random::get(-1.f, 1.f), 0.f};
    movementComponents.getComponent(entity)->direction = normalize(movementComponents.getComponent(entity)->direction);
    movementComponents.getComponent(entity)->position.x = Random::get(-20.f, 20.f);
    movementComponents.getComponent(entity)->position.y = Random::get(-20.f, 20.f);
}
