#pragma once

#include "ecs/EntityManager.hpp"

#include "components/Position.hpp"
#include "components/Life.hpp"
#include "components/Visibility.hpp"

#include "systems/System_1.hpp"
#include "systems/System_2.hpp"

#include "Debug.hpp"

class Game
{
public:
    Game();

    void draw();
    void update(float time);

private:
    ECS::EntitiesManager entityManager;
};
