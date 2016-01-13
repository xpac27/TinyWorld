#include "../../inc/ecs/SystemManager.hpp"
#include "../../inc/ecs/System.hpp"
#include "../../inc/ecs/ComponentManager.hpp"
#include "../../inc/systems/RenderSystem.hpp"
#include "../../inc/systems/MovementSystem.hpp"
#include "../utils/log.hpp"
#include <chrono>
#include <thread>

namespace ecs {

SystemManager::SystemManager(const char* _name)
    : name(_name)
{}

void SystemManager::setLatency(float seconds)
{
    latency = seconds;
}

void SystemManager::printStats()
{
    statistics.print(name);
}

void SystemManager::initialize()
{
    for (auto& system : systems) {
       system->initialize();
    }
}

void SystemManager::reload()
{
    for (auto& system : systems) {
       system->reload();
    }
}

void SystemManager::update()
{
    statistics.updating(); // TODO wrap that in the for loop and stat all systems
    for (auto& system : systems) {
        system->update();
    }
    statistics.updated();
    sleep();
}

void SystemManager::update(float seconds)
{
    float delta = seconds - previousUpdateCall;
    statistics.updating();
    previousUpdateCall = seconds;
    for (auto& system : systems) {
        system->update(seconds, delta);
    }
    statistics.updated();
    sleep();
}

void SystemManager::sleep()
{
    if (latency > 0.f) {
        std::this_thread::sleep_for(std::chrono::duration<float>(latency));
    }
}

void SystemManager::addRenderSystem(ecs::ComponentManager<Visibility>* visibilityComponents, ecs::ComponentManager<Movement>* movementComponents)
{
    addSystem(new RenderSystem(visibilityComponents, movementComponents));
}

void SystemManager::addMovementSystem(ecs::ComponentManager<Movement>* movementComponents)
{
    addSystem(new MovementSystem(movementComponents));
}

void SystemManager::addSystem(System* system)
{
    systems.push_back(system);
}
}
