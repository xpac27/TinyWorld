#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "Application.hpp"

void setupWindow(unsigned int width, unsigned int height);

using namespace sf;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    RenderWindow window(VideoMode(800, 600), "TinyWorld", (Style::Close | Style::Resize), settings);
    window.setVerticalSyncEnabled(true);

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

    setupWindow(800, 600);

    Application application;
    Clock clock;

    while (window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
            if (event.type == Event::Resized) setupWindow(event.size.width, event.size.height);
        }

        application.update(clock.getElapsedTime().asSeconds());

        if (clock.getElapsedTime().asMilliseconds() % 16 == 0) {
            glLoadIdentity();
            application.draw();
            window.display();
        }

        clock.restart();
    }

    return 0;
}
#include "helpers/Debug.hpp"

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
    Debug::printl(width, "x", height);
    Debug::printl(sceneWidth, "x", sceneHeight);
    glViewport(0, 0, GLsizei(width), GLsizei(height));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(sceneWidth / -2.f, sceneWidth / 2.f, sceneHeight / 2.f, sceneHeight / -2.f, 0.f, 1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
