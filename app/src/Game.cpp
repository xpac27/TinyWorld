#include "Game.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "utils/Random.hpp"

Game::Game()
{
    visualSystems.addSystem(new RenderSystem(&visibilityComponents, &movementComponents));
    simulationSystems.addSystem(new MovementSystem(&movementComponents));
    simulationSystems.setLatency(1000.f / 200.f);

    for (int i = 0; i < 100; i ++) {
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
    movementComponents.getComponent(entity)->velocity = Random::get(2.f, 10.f);
    movementComponents.getComponent(entity)->direction = {Random::get(-1.f, 1.f), Random::get(-1.f, 1.f), 0.f};
    movementComponents.getComponent(entity)->direction = normalize(movementComponents.getComponent(entity)->direction);
    movementComponents.getComponent(entity)->position.x = Random::get(-5.f, 5.f);
    movementComponents.getComponent(entity)->position.y = Random::get(-5.f, 5.f);
}
