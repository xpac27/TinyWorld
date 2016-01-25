#include "log.hpp"
#include "../../inc/components/Movement.hpp"
#include "../../inc/components/Life.hpp"
#include "../../inc/components/Visibility.hpp"

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
    switch (c->meshType) {
        case MeshType::PLAN: printl("  meshType: plan"); break;
        case MeshType::CUBE: printl("  meshType: cube"); break;
        case MeshType::SPHERE: printl("  meshType: sphere"); break;
        case MeshType::TORUS: printl("  meshType: torus"); break;
        case MeshType::TEAPOT: printl("  meshType: teapot"); break;
        case MeshType::TWISTED_TORUS: printl("  meshType: twisted-torus"); break;
    }
    printl("  scale: ", c->scale.x, c->scale.y, c->scale.z);
}
