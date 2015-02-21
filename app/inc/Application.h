#pragma once
#include "Game.h"

class Application
{
    public:

        void draw();
        void update(float time);

    private:

        Game game;
};
