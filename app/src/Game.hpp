#pragma once

#include "ecs/EntityManager.hpp"
#include "ecs/ComponentManager.hpp"

#include "components/Life.hpp"
#include "components/Position.hpp"
#include "components/Visibility.hpp"

class Game
{
public:

    Game();

    void draw();
    void update(float time);

private:

    ECS::EntityManager entities = {};

    ECS::ComponentManager<Life> lifeComponents = ECS::ComponentManager<Life>();
    ECS::ComponentManager<Position> positionComponents = ECS::ComponentManager<Position>();
    ECS::ComponentManager<Visibility> visibilityComponents = ECS::ComponentManager<Visibility>();
};
