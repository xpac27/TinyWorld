#include "Game.hpp"

Game::Game()
{
    entityManager.addSystem(System_1());
    entityManager.addSystem(System_2());

    Index e1 = entityManager.addEntity();
    Index e2 = entityManager.addEntity();
    Index e3 = entityManager.addEntity();

    Debug::printl("new entity #", e1);
    Debug::printl("new entity #", e2);
    Debug::printl("new entity #", e3);

    Debug::printl("total entities:", entityManager.getEntityCount());

    entityManager.addComponent<Position>(e1);
    entityManager.addComponent<Position>(e2);
    entityManager.addComponent<Position>(e3);
    entityManager.addComponent<Life>(e2);
    entityManager.addComponent<Life>(e3);
    entityManager.addComponent<Visibility>(e3);

    Debug::printl("entity #", e1, ":");
    Debug::dump(entityManager.getComponent<Position>(e1));

    Debug::printl("entity #", e2, ":");
    Debug::dump(entityManager.getComponent<Position>(e2));
    Debug::dump(entityManager.getComponent<Life>(e2));

    Debug::printl("entity #", e3, ":");
    Debug::dump(entityManager.getComponent<Position>(e3));
    Debug::dump(entityManager.getComponent<Life>(e3));
    Debug::dump(entityManager.getComponent<Visibility>(e3));
}

void Game::draw()
{
}

void Game::update(float time)
{
}
