#include "utils/Log.hpp"
#include "components/Movement.hpp"
#include "components/Life.hpp"
#include "components/Visibility.hpp"

void Log::nl()
{
    std::cout << "\033[0m" << std::endl;
}

void Log::style(Color foreground, Color background, Mode mode)
{
    std::cout << "\033[" << mode;
    if (foreground != NONE) std::cout << ";" << (foreground + 29);
    if (background != NONE) std::cout << ";" << (background + 39);
    std::cout << "m";
}

void Log::style(Color foreground, Mode mode)
{
    style(foreground, NONE, mode);
}

void Log::dump(ECS::id entity)
{
    printl("Entity", entity);
}

void Log::dump(Movement* c)
{
    printl("Movement");
    printl("  position: ", c->position.x, c->position.y, c->position.z);
    printl("  direction: ", c->direction.x, c->direction.y, c->direction.z);
    printl("  velocity: ", c->velocity);
}

void Log::dump(Life* c)
{
    printl("Life");
    printl("  amount:", c->amount);
}

void Log::dump(Visibility* c)
{
    printl("Visibility");
    switch (c->meshType) {
        case MeshType::PLAN: printl("  meshType: plan"); break;
        case MeshType::CUBE: printl("  meshType: cube"); break;
        case MeshType::CACODEMON: printl("  meshType: cacodemon"); break;
    }
    printl("  scale: ", c->scale.x, c->scale.y, c->scale.z);
}
