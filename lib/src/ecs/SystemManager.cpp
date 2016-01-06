#include "ecs/SystemManager.hpp"
#include "ecs/System.hpp"
#include "ecs/ComponentManager.hpp"
#include "systems/RenderSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "utils/Log.hpp"
#include <chrono>
#include <thread>

using namespace Log;

namespace ECS {

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

void SystemManager::addRenderSystem(ECS::ComponentManager<Visibility>* visibilityComponents, ECS::ComponentManager<Movement>* movementComponents)
{
    addSystem(new RenderSystem(visibilityComponents, movementComponents));
}

void SystemManager::addMovementSystem(ECS::ComponentManager<Movement>* movementComponents)
{
    addSystem(new MovementSystem(movementComponents));
}

void SystemManager::addSystem(System* system)
{
    systems.push_back(system);
}
}
