#pragma once

class Game;

class Application
{

public:

    Application();

    bool isRunning();
    void draw();
    void update(float seconds);
    void onKeyPressed(int key);

private:

    void checkReload();

    Game* game;

    bool running = true;
    bool reloadRequested = false;
};
