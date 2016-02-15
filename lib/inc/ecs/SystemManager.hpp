#pragma once
#include <ecs/SystemStatistics.hpp>
#include <vector>

// TODO indent classes and separate namespaces from forward declarations
struct Movement;
struct Visibility;
namespace ecs {
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

    void addRenderSystem(ecs::ComponentManager<Visibility>* visibilityComponents, ecs::ComponentManager<Movement>* movementComponents);
    void addMovementSystem(ecs::ComponentManager<Movement>* movementComponents);

private:

    void addSystem(System* system);
    void sleep();

    float latency = 0;
    float previousUpdateCall = 0.f;
    const char* name;

    SystemStatistics statistics;

    std::vector<System*> systems = {};
};
}
