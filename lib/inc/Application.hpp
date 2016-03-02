#pragma once
#include <ApplicationParams.hpp>

class Game;

class Application
{

public:

    Application();
    ~Application();

    void setup(ApplicationParams params);
    void onKeyPressed(int key);
    void update(float seconds);
    void draw();
    void tearDown();

    bool isRunning();

private:

    Game* game;

    bool running = true;
};
