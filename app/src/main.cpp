#include "Application.hpp"
#include "utils/FPS.hpp"
#include <cmath>
#include <stdlib.h>
#include <GL/glew.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

void setupWindow(unsigned int width, unsigned int height);
void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);

int main()
{
    srand(unsigned(time(NULL)));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    settings.depthBits = 24;

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "TinyWorld", (sf::Style::Close | sf::Style::Resize), settings);
    window.setVerticalSyncEnabled(false);

    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glClearDepth(GL_ONE);
    glClearStencil(GL_ZERO);
    glClearColor(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    setupWindow(1600, 1200);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return int(err);
    }

    Application application;

    // TODO handle that in a class within the app
    FPS loopRate = FPS("LPS");
    FPS frameRate = FPS("FPS");
    sf::Clock loopClock;
    sf::Clock frameClock;
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

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    const GLdouble pi = M_PI;
    GLdouble fW, fH;
    fH = tan((fovY / 2) / 180 * pi) * zNear;
    fH = tan(fovY / 360 * pi) * zNear;
    fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
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
    perspectiveGL(90.0f, GLfloat(width) / GLfloat(height), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
