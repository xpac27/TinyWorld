#include "RenderSystem.hpp"
#include "helpers/Debug.hpp"

void RenderSystem::update()
{
    // TODO try to use a for in loop
    // for (auto i : getEntities()) {
    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        Debug::printl(" >", getEntities()->at(i));
    }
    // Debug::printl(" > RenderSystem updated");
}
