#include <stdlib.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "Application.hpp"
#include "utils/FPS.hpp"
#include "graphic/Vertex.hpp"

void setupWindow(unsigned int width, unsigned int height);

using namespace std;

int main()
{
    srand(unsigned(time(NULL)));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(800, 600), "TinyWorld", (sf::Style::Close | sf::Style::Resize), settings);
    window.setVerticalSyncEnabled(false);

    glShadeModel(GL_SMOOTH);
    glCullFace(GL_FRONT);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_FALSE);
    glClearDepth(GL_ONE);
    glClearStencil(GL_ZERO);
    glClearColor(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    setupWindow(800, 600);

    sf::Clock loopClock;
    sf::Clock frameClock;
    Application application;
    FPS loopRate = FPS("LPS");
    FPS frameRate = FPS("FPS");

    sf::Time loopTime;
    sf::Time drawTime;

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) setupWindow(event.size.width, event.size.height);
        }

        application.update(loopClock.getElapsedTime().asSeconds());
        loopTime = loopClock.getElapsedTime();
        loopClock.restart();
        loopRate.tick();

        if (frameClock.getElapsedTime().asSeconds() > 1.f / 60.f - (drawTime + loopTime).asSeconds()) {
            frameClock.restart();
            glLoadIdentity();
            application.draw();
            window.display();
            drawTime = frameClock.getElapsedTime();
            frameClock.restart();
            frameRate.tick();
        }

    }

    return 0;
}

void setupWindow(unsigned int width, unsigned int height)
{
    float sceneWidth = 4.f;
    float sceneHeight = 3.f;
    if (width > height) {
        sceneWidth = 100.f;
        sceneHeight = 100.f * (float(height) / float(width));
    } else if (width < height) {
        sceneWidth = 100.f * (float(width) / float(height));
        sceneHeight = 100.f;
    } else {
        sceneWidth = 100.f;
        sceneHeight = 100.f;
    }
    glViewport(0, 0, GLsizei(width), GLsizei(height));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(sceneWidth / -2.f, sceneWidth / 2.f, sceneHeight / 2.f, sceneHeight / -2.f, -100.f, 100.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
