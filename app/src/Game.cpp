#include "Game.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/MovementSystem.hpp"
#include <cmath>

Game::Game()
{
    visualSystems.addSystem(new RenderSystem(&visibilityComponents, &movementComponents));
    simulationSystems.addSystem(new MovementSystem(&movementComponents));
    simulationSystems.setLatency(1000 / 20);

    for (int i = 0; i < 10; i ++) {
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

void Game::update(float milliseconds)
{
    simulationSystems.update(milliseconds);
}

void Game::addEntity()
{
    ECS::id entity = entities.addEntity();
    movementComponents.addComponent(entity);
    visibilityComponents.addComponent(entity);
    movementComponents.getComponent(entity)->velocity = float(rand() % 1000) / 1000.f * 10.f;
    movementComponents.getComponent(entity)->direction = {float(rand() % 2000 - 1000) / 1000.f, float(rand() % 2000 - 1000) / 1000.f, 0.f};
    movementComponents.getComponent(entity)->direction = normalize(movementComponents.getComponent(entity)->direction);
    movementComponents.getComponent(entity)->position.x = float(rand() % 30 - 15);
    movementComponents.getComponent(entity)->position.y = float(rand() % 30 - 15);
}
// TODO use this
// This will generate a number from 0.0 to 1.0, inclusive.
//
// float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
// This will generate a number from 0.0 to some arbitrary float, X:
//
// float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/X));
// This will generate a number from some arbitrary LO to some arbitrary HI:
//
// float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
