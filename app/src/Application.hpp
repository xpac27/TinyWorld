#pragma once

class Game;

class Application
{

public:

    Application();

    void draw();
    void update(float time);

private:

    Game* game;
};
