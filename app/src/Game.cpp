#include "Game.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/MovementSystem.hpp"
#include <cmath>

Game::Game()
{
    visualSystems.addSystem(new RenderSystem(&visibilityComponents, &movementComponents));
    simulationSystems.addSystem(new MovementSystem(&movementComponents));

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

void Game::update(long milliseconds)
{
    simulationSystems.update(milliseconds);
}

void Game::addEntity()
{
    ECS::id entity = entities.addEntity();
    movementComponents.addComponent(entity);
    visibilityComponents.addComponent(entity);
    // movementComponents.getComponent(entity)->position.x = float(rand() % 100 - 50);
    // movementComponents.getComponent(entity)->position.y = float(rand() % 100 - 50);
    // double r = rand();
    // movementComponents.getComponent(entity)->direction.x = float(sin(r));
    // movementComponents.getComponent(entity)->direction.y = float(cos(r));
}
