#include "Application.hpp"
#include "Game.hpp"

Application::Application()
    : game(nullptr)
{
}

Application::~Application()
{
    delete game;
}

void Application::setup(ApplicationParams params)
{
    if (game) delete game;

    game = new Game();
    game->load(params.rootPath);
}

void Application::onKeyPressed(int key)
{
    switch (key) {
        case 256: running = false; break; // ESC
    }
}

void Application::update(float seconds)
{
    game->update(seconds);
}

void Application::draw()
{
    game->draw();
}

bool Application::isRunning()
{
    return running;
}
