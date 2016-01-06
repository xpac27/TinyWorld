#pragma once
#include "ecs/SystemStatistics.hpp"
#include <vector>

struct Movement;
struct Visibility;
namespace ECS {
class System;
template <typename T> class ComponentManager;

class SystemManager
{

public:

    SystemManager(const char* _name);

    void setLatency(float seconds);
    void printStats();
    void initialize();
    void reload();
    void update();
    void update(float seconds);

    void addRenderSystem(ECS::ComponentManager<Visibility>* visibilityComponents, ECS::ComponentManager<Movement>* movementComponents);
    void addMovementSystem(ECS::ComponentManager<Movement>* movementComponents);

private:

    void addSystem(System* system);

    float latency = 0.f;
    float previousUpdateCall = 0.f;
    const char* name;

    SystemStatistics statistics;

    std::vector<System*> systems = {};
};
}
