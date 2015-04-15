#include "helpers/Debug.hpp"
#include "components/Position.hpp"
#include "components/Life.hpp"
#include "components/Visibility.hpp"

void Debug::dump(ECS::id entity)
{
    printl("Entity", entity);
}

void Debug::dump(Position* c)
{
    printl("Position");
    printl("  y:", c->x, "x:", c->y);
}

void Debug::dump(Life* c)
{
    printl("Life");
    printl("  amount:", c->amount);
}

void Debug::dump(Visibility* c)
{
    printl("Visibility");
}

void Debug::nl()
{
    std::cout << std::endl;
}
