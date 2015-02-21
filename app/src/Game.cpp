#include "Game.h"

Game::Game()
{
    entityManager.registerComponent<Position>();
    entityManager.registerComponent<Life>();
    entityManager.registerComponent<Visibility>();

    entityManager.registerSystem<System_1>();
    entityManager.registerSystem<System_2>();

    unsigned int e1 = entityManager.addEntity();
    unsigned int e2 = entityManager.addEntity();
    unsigned int e3 = entityManager.addEntity();

    Debug::print("new entity #");
    Debug::print("new entity #");
    Debug::print("new entity #");

    Debug::printl("total entities:", entityManager.getEntityCount());

    entityManager.addComponent<Position>(e1);
    entityManager.addComponent<Position>(e2);
    entityManager.addComponent<Position>(e3);
    entityManager.addComponent<Life>(e2);
    entityManager.addComponent<Life>(e3);
    entityManager.addComponent<Visibility>(e3);

    Debug::printl("entity #", e1, "has component position?", (entityManager.hasComponent<Position>(e1) ? "yes" : "no"));
    Debug::printl("entity #", e1, "has component life?", (entityManager.hasComponent<Life>(e1) ? "yes" : "no"));
    Debug::printl("entity #", e1, "has component visibility?", (entityManager.hasComponent<Visibility>(e1) ? "yes" : "no"));

    Debug::printl("entity #", e2, "has component position?", (entityManager.hasComponent<Position>(e2) ? "yes" : "no"));
    Debug::printl("entity #", e2, "has component life?", (entityManager.hasComponent<Life>(e2) ? "yes" : "no"));
    Debug::printl("entity #", e2, "has component visibility?", (entityManager.hasComponent<Visibility>(e2) ? "yes" : "no"));

    Debug::printl("entity #", e3, "has component position?", (entityManager.hasComponent<Position>(e3) ? "yes" : "no"));
    Debug::printl("entity #", e3, "has component life?", (entityManager.hasComponent<Life>(e3) ? "yes" : "no"));
    Debug::printl("entity #", e3, "has component visibility?", (entityManager.hasComponent<Visibility>(e3) ? "yes" : "no"));

    Debug::printl("entity #", e1, ":");
    Debug::print(entityManager.getComponent<Position>(e1));

    Debug::printl("entity #", e2, ":");
    Debug::print(entityManager.getComponent<Position>(e2));
    Debug::print(entityManager.getComponent<Life>(e2));

    Debug::printl("entity #", e3, ":");
    Debug::print(entityManager.getComponent<Position>(e3));
    Debug::print(entityManager.getComponent<Life>(e3));
    Debug::print(entityManager.getComponent<Visibility>(e3));
}

void Game::draw()
{
}

void Game::update(float time)
{
}