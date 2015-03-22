#include "Game.hpp"

#include "helpers/Debug.hpp"

Game::Game()
{
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

    Debug::printl("new entity, id:", e1);
    Debug::printl("new entity, id:", e2);
    Debug::printl("new entity, id:", e3);

    Debug::printl("total entities:", entities.getTotal());

    Debug::printl("entity #", e1, ":");
    Debug::dump(positionComponents.getComponent(e1));
    Debug::dump(visibilityComponents.getComponent(e1));
    Debug::dump(lifeComponents.getComponent(e1));

    Debug::printl("entity #", e2, ":");
    Debug::dump(positionComponents.getComponent(e2));
    Debug::dump(visibilityComponents.getComponent(e2));

    Debug::printl("entity #", e3, ":");
    Debug::dump(positionComponents.getComponent(e3));
}

void Game::draw()
{
}

void Game::update(float time)
{
    // system1.update(time);
    // system2.update(time);
}
