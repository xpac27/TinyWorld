#include "Game.hpp"

#include <systems/RenderSystem.hpp>
#include <systems/MovementSystem.hpp>
#include <utils/Random.hpp>

#include <glm/detail/func_geometric.hpp>

Game::Game()
    : visualSystems("VIS")
    , simulationSystems("SIM")
{
    visualSystems.addRenderSystem(&visibilityComponents, &movementComponents);
    visualSystems.initialize();

    simulationSystems.addMovementSystem(&movementComponents);
    simulationSystems.setLatency(1.f / 10.f);
    simulationSystems.initialize();

    // setupWorld();
    addTestEntity();
    // for (int i = 0; i < 10; i ++) {
    //     addEntity();
    // }
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

void Game::reload()
{
    visualSystems.reload();
    simulationSystems.reload();
}

void Game::setupWorld()
{
    ecs::id entity = entities.addEntity();
    visibilityComponents.addComponent(entity);
    visibilityComponents.getComponent(entity)->meshType = MeshType::PLAN;
    visibilityComponents.getComponent(entity)->scale = glm::vec3(80, 80, 1);
}

void Game::addEntity()
{
    ecs::id entity = entities.addEntity();
    movementComponents.addComponent(entity);
    visibilityComponents.addComponent(entity);
    visibilityComponents.getComponent(entity)->meshType = MeshType::CUBE;
    visibilityComponents.getComponent(entity)->scale = glm::vec3(1.f, 1.f, 1.f);
    movementComponents.getComponent(entity)->velocity = Random::get(2.f, 5.f);
    movementComponents.getComponent(entity)->direction = normalize(glm::vec3(Random::get(-1.f, 1.f), Random::get(-1.f, 1.f), 0.f));
    movementComponents.getComponent(entity)->position.x = Random::get(-6.f, 6.f);
    movementComponents.getComponent(entity)->position.y = Random::get(-6.f, 6.f);
    movementComponents.getComponent(entity)->position.z = 0.5f;
}

void Game::addTestEntity()
{
    ecs::id entity = entities.addEntity();
    movementComponents.addComponent(entity);
    visibilityComponents.addComponent(entity);
    visibilityComponents.getComponent(entity)->meshType = MeshType::TORUS;
    visibilityComponents.getComponent(entity)->scale = glm::vec3(4.0f, 4.0f, 4.0f);
    movementComponents.getComponent(entity)->direction = glm::vec3(0.f, -1.f, 0.f);
    movementComponents.getComponent(entity)->position.x = 0.0f;
    movementComponents.getComponent(entity)->position.y = -2.0f;
    movementComponents.getComponent(entity)->position.z = 2.0f;
}
