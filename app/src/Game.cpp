#include "Game.hpp"
#include "systems/RenderSystem.hpp"

#include "helpers/Debug.hpp"

Game::Game()
{
    visualSystems.addSystem(new RenderSystem(&visibilityComponents, &positionComponents));

    ECS::id e1 = entities.addEntity();
    ECS::id e2 = entities.addEntity();
    ECS::id e3 = entities.addEntity();

    positionComponents.addComponent(e1);
    positionComponents.addComponent(e2);
    positionComponents.addComponent(e3);

    visibilityComponents.addComponent(e1);
    visibilityComponents.addComponent(e2);

    lifeComponents.addComponent(e1);

    Debug::printl("total entities:", entities.getTotal());

    Debug::dump(e1);
    Debug::dump(positionComponents.getComponent(e1));
    Debug::dump(visibilityComponents.getComponent(e1));
    Debug::dump(lifeComponents.getComponent(e1));

    Debug::dump(e2);
    Debug::dump(positionComponents.getComponent(e2));
    Debug::dump(visibilityComponents.getComponent(e2));

    Debug::dump(e3);
    Debug::dump(positionComponents.getComponent(e3));
}

void Game::update(float time)
{
    simulationSystems.update(time);
}

void Game::draw()
{
    visualSystems.update();
}
