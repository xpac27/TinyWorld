#pragma once
#include "EntityManager.h"
#include "Component.h"
#include "components/Position.h"
#include "components/Life.h"
#include "components/Visibility.h"
#include "systems/System_1.h"
#include "systems/System_2.h"
#include "Debug.h"

class Game
{
    public:

        Game();

        void draw();
        void update(float time);

    private:

        EntitiesManager entityManager;
};
