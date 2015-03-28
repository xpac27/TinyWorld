#include "RenderSystem.hpp"
#include "helpers/Debug.hpp"

void RenderSystem::update()
{
    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        Debug::printl(" >", getEntities()->at(i));
    }
}
