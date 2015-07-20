#pragma once
#include <vector>

struct Movement;
struct Visibility;

namespace ECS {
class System;
class SystemStatistics;
template <typename T> class ComponentManager;

class SystemManager
{

public:

    SystemManager(const char* _name);
    ~SystemManager();

    void setLatency(float seconds);
    void printStats();
    void initialize();
    void update();
    void update(float seconds);

    void addRenderSystem(ECS::ComponentManager<Visibility>* visibilityComponents, ECS::ComponentManager<Movement>* movementComponents);
    void addMovementSystem(ECS::ComponentManager<Movement>* movementComponents);

private:

    void addSystem(System* system);

    float latency = 0.f;
    float previousUpdateCall = 0.f;

    const char* name;

    SystemStatistics* statistics;

    std::vector<System*> systems = {};
};
}
