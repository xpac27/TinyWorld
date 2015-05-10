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

void Application::update(long milliseconds)
{
    game->update(milliseconds);
}

void Application::keyCallback(int key, int /*scancode*/, int action, int /*mods*/)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        running = false;
    }
}
