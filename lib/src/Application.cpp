#include "Application.hpp"
#include "Game.hpp"

Application::Application()
    : game(new Game())
{
}

Application::~Application()
{
    delete game;
}

void Application::setup(ApplicationParams params)
{
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

void Application::tearDown()
{
}

bool Application::isRunning()
{
    return running;
}
