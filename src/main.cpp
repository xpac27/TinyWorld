#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

void setupOpenGL()
{
    glShadeModel(GL_SMOOTH);
    glCullFace(GL_FRONT);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_FALSE);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glClearDepth(GL_ONE);
    glClearStencil(GL_ZERO);
    glClearColor(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
}

void setupWindow(float width, float height)
{
    float sceneWidth = 4.f;
    float sceneHeight = 3.f;
    if (width > height)
    {
        sceneWidth = 100.f;
        sceneHeight = 100.f * (height / width);
    }
    else if (width < height)
    {
        sceneWidth = 100.f * (width / height);
        sceneHeight = 100.f;
    }
    else
    {
        sceneWidth = 100.f;
        sceneHeight = 100.f;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(sceneWidth / -2.f, sceneWidth / 2.f, sceneHeight / 2.f, sceneHeight / -2.f, 0.f, 1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "WIP", (sf::Style::Close | sf::Style::Resize));
    sf::Clock clock;

    setupOpenGL();
    setupWindow(800, 600);

    // Game game;

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        sf::Event Event;
        while (window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)    window.close();
            if (Event.type == sf::Event::Resized)   setupWindow(Event.size.width, Event.size.height);
        }

        glLoadIdentity();

        // game.update(clock.getElapsedTime().asSeconds());
        clock.restart();

        // game.draw();

        window.display();
    }
}
