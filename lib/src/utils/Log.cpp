#include "Log.hpp"
#include "../components/Movement.hpp"
#include "../components/Life.hpp"
#include "../components/Visibility.hpp"

void nl()
{
    std::cout << "\033[0m" << std::endl;
}

void style(Color foreground, Color background, Mode mode)
{
    std::cout << "\033[" << mode;
    if (foreground != NONE) std::cout << ";" << (foreground + 29);
    if (background != NONE) std::cout << ";" << (background + 39);
    std::cout << "m";
}

void style(Color foreground, Mode mode)
{
    style(foreground, NONE, mode);
}

void dump(ecs::id entity)
{
    printl("Entity", entity);
}

void dump(Movement* c)
{
    printl("Movement");
    printl("  position: ", c->position.x, c->position.y, c->position.z);
    printl("  direction: ", c->direction.x, c->direction.y, c->direction.z);
    printl("  velocity: ", c->velocity);
}

void dump(Life* c)
{
    printl("Life");
    printl("  amount:", c->amount);
}

void dump(Visibility* c)
{
    printl("Visibility");
    printl("  meshId: ", c->meshId);
    printl("  scale: ", c->scale.x, c->scale.y, c->scale.z);
}
