#pragma once
#include "EntityManager.h"

class Game
{
    public:

        void draw();
        void update(float time);

    private:

        EntitiesManager entityManager;
};
