#include "Debug.hpp"

void Debug::dump(Position* p)
{
    return printl("- Position", "y:", p->x, "x:", p->y);
}

void Debug::dump(Life* p)
{
    printl("- Life", " amount:", p->amount);
}

void Debug::dump(Visibility* p)
{
    printl("- Visibility", " active:", p->active);
}
