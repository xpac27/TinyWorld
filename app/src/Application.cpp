#include "Application.hpp"
#include "Game.hpp"
#include <GLFW/glfw3.h>

Application::Application()
    : game(new Game())
{}

bool Application::isRunning()
{
    return running;
}

void Application::draw()
{
    game->draw();
}

void Application::update(float seconds)
{
    game->update(seconds);
}

void Application::keyCallback(int key, int /*scancode*/, int action, int /*mods*/)
{
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE: running = false; break;
            case GLFW_KEY_SPACE: game->printStats(); break;
        }
    }
}
