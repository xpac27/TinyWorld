#include "Game.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/MovementSystem.hpp"
#include <cmath>

Game::Game()
{
    visualSystems.addSystem(new RenderSystem(&visibilityComponents, &movementComponents));
    simulationSystems.addSystem(new MovementSystem(&movementComponents));
    simulationSystems.setLatency(1000 / 20);

    for (int i = 0; i < 1; i ++) {
        addEntity();
    }

    simulationSystems.initialize();
    visualSystems.initialize();
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

void Game::update(double milliseconds)
{
    simulationSystems.update(milliseconds);
}

void Game::addEntity()
{
    ECS::id entity = entities.addEntity();
    movementComponents.addComponent(entity);
    visibilityComponents.addComponent(entity);
    movementComponents.getComponent(entity)->velocity = float(rand() % 1000) / 1000.f;
    // movementComponents.getComponent(entity)->position.x = float(rand() % 30 - 15);
    // movementComponents.getComponent(entity)->position.y = float(rand() % 30 - 15);
    // movementComponents.getComponent(entity)->rotation.z = float(sin(rand()) * M_PI);
}
