#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "Application.h"

void setupWindow(unsigned int width, unsigned int height);

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "WIP", (Style::Close |
    Style::Resize));

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

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)    window.close();
            if (event.type == Event::Resized)   setupWindow(event.size.width,
            event.size.height);
        }

        glLoadIdentity();
        application.update(clock.getElapsedTime().asSeconds());
        application.draw();
        window.display();
        clock.restart();
    }

    return 1;
}

void setupWindow(unsigned int width, unsigned int height)
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
    glViewport(0, 0, GLsizei(width), GLsizei(height));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(sceneWidth / -2.f, sceneWidth / 2.f, sceneHeight / 2.f,
    sceneHeight / -2.f, 0.f, 1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// #include "main.h"


// --------------------------------------------------------------------------------- GAME
// void Game::start()
// {
//     entityManager.registerComponent<Position>();
//     entityManager.registerComponent<Life>();
//     entityManager.registerComponent<Visibility>();
//
//     entityManager.registerSystem<System_1>();
//     entityManager.registerSystem<System_2>();
//
//     unsigned int e1 = entityManager.addEntity();
//     unsigned int e2 = entityManager.addEntity();
//     unsigned int e3 = entityManager.addEntity();
//
//     std::cout << std::endl;
//     std::cout << "new entity #" << e1 << std::endl;
//     std::cout << "new entity #" << e2 << std::endl;
//     std::cout << "new entity #" << e3 << std::endl;
//
//     std::cout << std::endl;
//     std::cout << "total entities: " << entityManager.getEntityCount() << std::endl;
//
//     entityManager.addComponent<Position>(e1);
//     entityManager.addComponent<Position>(e2);
//     entityManager.addComponent<Position>(e3);
//     entityManager.addComponent<Life>(e2);
//     entityManager.addComponent<Life>(e3);
//     entityManager.addComponent<Visibility>(e3);
//
//     std::cout << std::endl;
//     std::cout << "entity #" << e1 << " has component position? " << (entityManager.hasComponent<Position>(e1) ? "yes" : "no") << std::endl;
//     std::cout << "entity #" << e1 << " has component life? " << (entityManager.hasComponent<Life>(e1) ? "yes" : "no") << std::endl;
//     std::cout << "entity #" << e1 << " has component visibility? " << (entityManager.hasComponent<Visibility>(e1) ? "yes" : "no") << std::endl;
//     std::cout << std::endl;
//     std::cout << "entity #" << e2 << " has component position? " << (entityManager.hasComponent<Position>(e2) ? "yes" : "no") << std::endl;
//     std::cout << "entity #" << e2 << " has component life? " << (entityManager.hasComponent<Life>(e2) ? "yes" : "no") << std::endl;
//     std::cout << "entity #" << e2 << " has component visibility? " << (entityManager.hasComponent<Visibility>(e2) ? "yes" : "no") << std::endl;
//     std::cout << std::endl;
//     std::cout << "entity #" << e3 << " has component position? " << (entityManager.hasComponent<Position>(e3) ? "yes" : "no") << std::endl;
//     std::cout << "entity #" << e3 << " has component life? " << (entityManager.hasComponent<Life>(e3) ? "yes" : "no") << std::endl;
//     std::cout << "entity #" << e3 << " has component visibility? " << (entityManager.hasComponent<Visibility>(e3) ? "yes" : "no") << std::endl;
//
//     std::cout << std::endl;
//     std::cout << "entity #" << e1 << ":" << std::endl;
//     print(entityManager.getComponent<Position>(e1));
//
//
//     std::cout << std::endl;
//     std::cout << "entity #" << e2 << ":" << std::endl;
//     print(entityManager.getComponent<Position>(e2));
//     print(entityManager.getComponent<Life>(e2));
//
//     std::cout << std::endl;
//     std::cout << "entity #" << e3 << ":" << std::endl;
//     print(entityManager.getComponent<Position>(e3));
//     print(entityManager.getComponent<Life>(e3));
//     print(entityManager.getComponent<Visibility>(e3));
// }

// template <class T>
// void print(const T* p);
// std::ostream& operator <<(std::ostream& os, const Position* p);
// std::ostream& operator <<(std::ostream& os, const Life* p);
// std::ostream& operator <<(std::ostream& os, const Visibility* p);
//
// template <class T>
// void print(const T* p)
// {
//     std::cout << p << std::endl;
// }
// std::ostream& operator <<(std::ostream& os, const Position* p)
// {
//     return os << "- Position"
//         << " y:" << p->x
//         << " x:" << p->y;
// }
// std::ostream& operator <<(std::ostream& os, const Life* p)
// {
//     return os << "- Life"
//         << " amount:" << p->amount;
// }
// std::ostream& operator <<(std::ostream& os, const Visibility* p)
// {
//     return os << "- Visibility"
//         << " active:" << p->active;
// }
