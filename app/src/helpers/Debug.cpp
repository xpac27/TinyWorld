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
    // TODO implement
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
        case MeshType::SQUARE: printl("  meshType: SQAURE"); break;
        case MeshType::PYRAMID: printl("  meshType: PYRAMID"); break;
        case MeshType::CUBE: printl("  meshType: CUBE"); break;
    }
}

void Debug::nl()
{
    std::cout << std::endl;
}
