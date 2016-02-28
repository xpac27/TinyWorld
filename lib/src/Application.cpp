#include "Application.hpp"
#include "Game.hpp"

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
    checkReload();
}

void Application::update(float seconds)
{
    game->update(seconds);
}

void Application::onKeyPressed(int key)
{
    switch (key) {
        case 256: running = false; break; // ESC
        case 82: reloadRequested = true; break; // R
    }
}

void Application::checkReload()
{
    if (reloadRequested) {
        game->reload();
        reloadRequested = false;
    }
}
