#include "Game.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "utils/Random.hpp"
#include <glm/detail/func_geometric.hpp>

Game::Game()
    : visualSystems("VIS")
    , simulationSystems("SIM")
{
    visualSystems.addRenderSystem(&visibilityComponents, &movementComponents);
    visualSystems.initialize();

    simulationSystems.addMovementSystem(&movementComponents);
    simulationSystems.setLatency(1.f / 100.f);
    simulationSystems.initialize();

    setupWorld();
    for (int i = 0; i < 100; i ++) {
        addEntity();
    }
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

void Game::update(float seconds)
{
    simulationSystems.update(seconds);
}

void Game::setupWorld()
{
    ECS::id entity = entities.addEntity();
    visibilityComponents.addComponent(entity);
    visibilityComponents.getComponent(entity)->meshType = MeshType::PLAN;
    visibilityComponents.getComponent(entity)->scale = glm::vec3(80, 80, 1);
}

void Game::addEntity()
{
    ECS::id entity = entities.addEntity();
    movementComponents.addComponent(entity);
    visibilityComponents.addComponent(entity);
    visibilityComponents.getComponent(entity)->meshType = MeshType::SPHERE;
    visibilityComponents.getComponent(entity)->scale = glm::vec3(1, 1, 1);
    movementComponents.getComponent(entity)->velocity = Random::get(0.5f, 2.f);
    movementComponents.getComponent(entity)->direction = {Random::get(-1.f, 1.f), Random::get(-1.f, 1.f), 0.f};
    movementComponents.getComponent(entity)->direction = normalize(movementComponents.getComponent(entity)->direction);
    movementComponents.getComponent(entity)->position.x = Random::get(-8.f, 8.f);
    movementComponents.getComponent(entity)->position.y = Random::get(-8.f, 8.f);
    movementComponents.getComponent(entity)->position.z = 1.0f;
}
