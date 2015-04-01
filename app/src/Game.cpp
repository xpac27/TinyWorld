#include <stdlib.h>
#include "Game.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "helpers/Debug.hpp"

Game::Game()
{
    srand(unsigned(time(NULL)));

    visualSystems.addSystem(new RenderSystem(&visibilityComponents, &positionComponents));
    visualSystems.addSystem(new MovementSystem(&positionComponents, &physicsComponents));

    for (int i = 0; i < 100; i ++) {
        addEntity();
    }
}

void Game::update(float time)
{
    simulationSystems.update(time);
}

void Game::draw()
{
    visualSystems.update();
}

void Game::addEntity()
{
    ECS::id entity = entities.addEntity();
    positionComponents.addComponent(entity);
    visibilityComponents.addComponent(entity);
    physicsComponents.addComponent(entity);
    positionComponents.getComponent(entity)->x = 0.f;
    positionComponents.getComponent(entity)->y = 0.f;
    physicsComponents.getComponent(entity)->velocity_x = float(rand() % 100 - 50) / 100.f;
    physicsComponents.getComponent(entity)->velocity_y = float(rand() % 100 - 50) / 100.f;
}
