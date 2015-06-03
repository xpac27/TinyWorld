#include "utils/Log.hpp"
#include "components/Movement.hpp"
#include "components/Life.hpp"
#include "components/Visibility.hpp"

void Log::dump(ECS::id entity)
{
    printl("Entity", entity);
}

void Log::dump(Movement* c)
{
    printl("Movement");
    printl("  position: ", c->position.x, c->position.y, c->position.z);
    // printl("  rotation: ", c->rotation.x, c->rotation.y, c->rotation.z);
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
        case MeshType::CUBE: printl("  meshType: cube"); break;
        case MeshType::CACODEMON: printl("  meshType: cacodemon"); break;
        case MeshType::FLAN: printl("  meshType: flan"); break;
    }
}

void Log::nl()
{
    std::cout << std::endl;
}
