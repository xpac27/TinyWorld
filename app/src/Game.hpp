#pragma once

#include <ecs/EntityManager.hpp>
#include <ecs/ComponentManager.hpp>

#include <systems/RenderSystem.hpp>
#include <systems/MovementSystem.hpp>

#include <components/Life.hpp>
#include <components/Movement.hpp>
#include <components/Visibility.hpp>

#include <graphic/Renderer.hpp>
#include <graphic/MeshStore.hpp>
#include <graphic/ProgramStore.hpp>

#include <utils/Store.hpp>

class Cubemap;
class CubemapParams;

class Game
{
public:

    Game();

    void draw();
    void update(float seconds);
    void reload();

private:

    float previousUpdateSeconds = 0.f;

    void setupWorld();
    void addEntity();
    void addTestEntity();

    ecs::EntityManager entities;

    ecs::ComponentManager<Life> lifeComponents = ecs::ComponentManager<Life>();
    ecs::ComponentManager<Movement> movementComponents = ecs::ComponentManager<Movement>();
    ecs::ComponentManager<Visibility> visibilityComponents = ecs::ComponentManager<Visibility>();

    RenderSystem renderSystem;
    MovementSystem movementSystem;

    Renderer renderer;
    MeshStore meshStore;
    ProgramStore programStore;

    Store<const char*, Cubemap, CubemapParams> cubemapStore;
};
