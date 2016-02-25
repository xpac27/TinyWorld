#include "Game.hpp"

#include <systems/RenderSystem.hpp>
#include <systems/MovementSystem.hpp>

#include <utils/Random.hpp>
#include <glm/detail/func_geometric.hpp>

Game::Game()
    : renderSystem(&visibilityComponents, &movementComponents)
    , movementSystem(&movementComponents)
    , renderer(meshStore, programStore, cubemapStore)
{
    setupWorld();
    addTestEntity();
    // for (auto i(0u); i < 10; i ++) addEntity();
}

void Game::draw()
{
    renderSystem.update(renderer);
}

void Game::update(float seconds)
{
    movementSystem.update(seconds - previousUpdateSeconds);
    previousUpdateSeconds = seconds;
}

void Game::reload()
{
    meshStore.reloadMeshesTextures();
    programStore.reloadProgramesShaders();
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
    visibilityComponents.getComponent(entity)->meshType = MeshType::TWISTED_TORUS;
    visibilityComponents.getComponent(entity)->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    movementComponents.getComponent(entity)->direction = glm::vec3(0.f, -1.f, 0.f);
    movementComponents.getComponent(entity)->position.x = 0.0f;
    movementComponents.getComponent(entity)->position.y = -2.0f;
    movementComponents.getComponent(entity)->position.z = 2.0f;
}
