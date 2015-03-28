#include "Game.hpp"
#include "systems/RenderSystem.hpp"

#include "helpers/Debug.hpp"

Game::Game()
{
    visualSystems.addSystem(new RenderSystem(&visibilityComponents, &positionComponents));

    ECS::id e1 = entities.addEntity();
    ECS::id e2 = entities.addEntity();
    ECS::id e3 = entities.addEntity();

    Position *p1 = positionComponents.createComponent();
    Position *p2 = positionComponents.createComponent();
    Position *p3 = positionComponents.createComponent();

    Visibility *v1 = visibilityComponents.createComponent();
    Visibility *v2 = visibilityComponents.createComponent();

    Life *l1 = lifeComponents.createComponent();

    positionComponents.addComponent(p1, e1);
    positionComponents.addComponent(p2, e2);
    positionComponents.addComponent(p3, e3);

    visibilityComponents.addComponent(v1, e1);
    visibilityComponents.addComponent(v2, e2);

    lifeComponents.addComponent(l1, e1);

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
