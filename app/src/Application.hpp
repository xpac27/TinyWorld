#pragma once

class Game;

class Application
{

public:

    Application();

    bool isRunning();
    void draw();
    void update(float seconds);
    void keyCallback(int key, int scancode, int action, int mods);

private:

    void checkReload();

    Game* game;

    bool running = true;
    bool reloadRequested = false;
};
