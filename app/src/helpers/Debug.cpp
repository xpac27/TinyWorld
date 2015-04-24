#include "helpers/Debug.hpp"
#include "components/Movement.hpp"
#include "components/Life.hpp"
#include "components/Visibility.hpp"

void Debug::dump(ECS::id entity)
{
    printl("Entity", entity);
}

void Debug::dump(Movement* c)
{
    printl("Movement");
    printl("  position: ", c->position.x, c->position.y);
    printl("  direction: ", c->direction.x, c->direction.y);
}

void Debug::dump(Life* c)
{
    printl("Life");
    printl("  amount:", c->amount);
}

void Debug::dump(Visibility* c)
{
    printl("Visibility");
    switch (c->meshType) {
        case MeshType::CUBE: printl("  meshType: cube"); break;
        case MeshType::SQUARE: printl("  meshType: square"); break;
        case MeshType::PYRAMID: printl("  meshType: pyramid"); break;
        case MeshType::GOOMBA: printl("  meshType: goomba"); break;
        case MeshType::CACODEMON: printl("  meshType: cacodemon"); break;
    }
}

void Debug::nl()
{
    std::cout << std::endl;
}
