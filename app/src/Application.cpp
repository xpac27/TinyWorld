#include "Application.hpp"
#include "Game.hpp"

Application::Application()
    : game(new Game())
{}

void Application::draw()
{
    game->draw();
}

void Application::update(float time)
{
    game->update(time);
}
