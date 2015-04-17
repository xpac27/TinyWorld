#include "Game.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "helpers/Debug.hpp"
#include <SFML/OpenGL.hpp>

Game::Game()
{
    visualSystems.addSystem(new RenderSystem(&visibilityComponents, &positionComponents));
    simulationSystems.addSystem(new MovementSystem(&positionComponents, &physicsComponents));

    for (int i = 0; i < 1000; i ++) {
        addEntity();
    }

    simulationSystems.initialize();
    visualSystems.initialize();
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
