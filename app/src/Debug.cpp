#include "Debug.h"

void Debug::print(Position* p)
{
    return printl("- Position", "y:", p->x, "x:", p->y);
}

void Debug::print(Life* p)
{
    printl("- Life", " amount:", p->amount);
}

void Debug::print(Visibility* p)
{
    printl("- Visibility", " active:", p->active);
}
