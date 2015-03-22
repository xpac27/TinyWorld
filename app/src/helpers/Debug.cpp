#include "helpers/Debug.hpp"
#include "components/Position.hpp"
#include "components/Life.hpp"
#include "components/Visibility.hpp"

void Debug::dump(Position &c)
{
    return printl("- Position", "y:", c.x, "x:", c.y);
}

void Debug::dump(Life &c)
{
    printl("- Life", " amount:", c.amount);
}

void Debug::dump(Visibility &c)
{
    printl("- Visibility", " active:", c.active);
}
