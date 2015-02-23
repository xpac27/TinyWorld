#pragma once
#include "Game.hpp"

class Application
{
public:
    void draw();
    void update(float time);

private:
    Game game;
};
