// #include <SFML/OpenGL.hpp>
// #include <SFML/Graphics.hpp>

// #include "Application.h"

// void setupWindow(unsigned int width, unsigned int height);

// using namespace sf;

// int main()
// {
//     RenderWindow window(VideoMode(800, 600), "WIP", (Style::Close | Style::Resize));
//
//     glShadeModel(GL_SMOOTH);
//     glCullFace(GL_FRONT);
//     glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//     glDisable(GL_CULL_FACE);
//     glDisable(GL_DEPTH_TEST);
//     glDisable(GL_STENCIL_TEST);
//     glDepthMask(GL_FALSE);
//     glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
//     glClearDepth(GL_ONE);
//     glClearStencil(GL_ZERO);
//     glClearColor(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
//
//     setupWindow(800, 600);
//
//     Application application;
//     Clock clock;
//
//     while (window.isOpen())
//     {
//         if (Keyboard::isKeyPressed(Keyboard::Escape))
//             window.close();
//
//         Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == Event::Closed)    window.close();
//             if (event.type == Event::Resized)   setupWindow(event.size.width, event.size.height);
//         }
//
//         glLoadIdentity();
//         application.update(clock.getElapsedTime().asSeconds());
//         application.draw();
//         window.display();
//         clock.restart();
//     }
// }

// void setupWindow(unsigned int width, unsigned int height)
// {
//     float sceneWidth = 4.f;
//     float sceneHeight = 3.f;
//     if (width > height)
//     {
//         sceneWidth = 100.f;
//         sceneHeight = 100.f * (height / width);
//     }
//     else if (width < height)
//     {
//         sceneWidth = 100.f * (width / height);
//         sceneHeight = 100.f;
//     }
//     else
//     {
//         sceneWidth = 100.f;
//         sceneHeight = 100.f;
//     }
//     glViewport(0, 0, GLsizei(width), GLsizei(height));
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(sceneWidth / -2.f, sceneWidth / 2.f, sceneHeight / 2.f, sceneHeight / -2.f, 0.f, 1.f);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
// }

#include <iostream>
#include "main.h"

int main()
{
    Game game;
    game.start();
}

void Game::start()
{
    unsigned int e1 = entityManager.addEntity();
    unsigned int e2 = entityManager.addEntity();
    unsigned int e3 = entityManager.addEntity();
    
    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;
    std::cout << e3 << std::endl;

    entityManager.addComponentToEntity(e1, Component::Type::position);

    entityManager.addComponentToEntity(e2, Component::Type::position);
    entityManager.addComponentToEntity(e2, Component::Type::life);

    entityManager.addComponentToEntity(e3, Component::Type::position);
    entityManager.addComponentToEntity(e3, Component::Type::life);
    entityManager.addComponentToEntity(e3, Component::Type::visibility);
}

unsigned int EntitiesManager::addEntity()
{
    entities.push_back(Entity()); 
    return (++totalEntities) - 1;
}

void EntitiesManager::addComponentToEntity(unsigned int entityIndex, Component::Type componentType)
{
    unsigned int index = 0;
    switch (componentType)
    {
        case Component::Type::position: 
            index = unsigned(positionComponents.size());
            positionComponents.push_back(Component::Position());
            break;
        case Component::Type::visibility: 
            index = unsigned(visibilityComponents.size());
            visibilityComponents.push_back(Component::Visibility());
            break;
        case Component::Type::life: 
            index = unsigned(lifeComponents.size());
            lifeComponents.push_back(Component::Life());
            break;
    }
    entities[entityIndex].componentIndexes[componentType] = index;
}


