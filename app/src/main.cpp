// #include <SFML/OpenGL.hpp>
// #include <SFML/Graphics.hpp>

// #include "Application.h"

// void setupWindow(unsigned int width, unsigned int height);

// using namespace sf;

// int main()
// {
//     RenderWindow window(VideoMode(800, 600), "WIP", (Style::Close |
//     Style::Resize));
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
//             if (event.type == Event::Resized)   setupWindow(event.size.width,
//             event.size.height);
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
//     glOrtho(sceneWidth / -2.f, sceneWidth / 2.f, sceneHeight / 2.f,
//     sceneHeight / -2.f, 0.f, 1.f);
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

// --------------------------------------------------------------------------------- GAME
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

// --------------------------------------------------------------------------------- SYSTEM
bool System::hasComponentType(Component::Type type) const
{
    return componentTypes & mask(type);
}
void System::registerEntity(unsigned int entity)
{
    entities.push_back(entity);
}
void System::unregisterEntity(unsigned int entity)
{
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end())
    {
        entities.erase(it);
    }
}

// --------------------------------------------------------------------------------- ENTITY MANAGER

unsigned int EntitiesManager::addEntity()
{
    entitiesComponentsIndex.push_back({{-1}});
    return ++entityCount;
}

void EntitiesManager::addComponentToEntity(unsigned int entity, Component::Type componentType)
{
    // Create a new component
    int componentIndex = 0;
    switch (componentType)
    {
        // TODO use template
        case Component::Type::position: componentIndex = addPositionComponent(); break;
        case Component::Type::visibility: componentIndex = addVisibilityComponent(); break;
        case Component::Type::life: componentIndex = addLifeComponent(); break;
    }

    // Register component's index for this entity
    entitiesComponentsIndex.at(entity)[componentType] = componentIndex;

    // Check witch system should know about this entity
    registerEntity(entity, componentType);
}

void EntitiesManager::deleteComponentFromEntity(unsigned int entity, Component::Type componentType)
{
    // Delete the component instance
    deleteComponent(componentType, entitiesComponentsIndex.at(entity)[componentType]);

    // Remove component's index for this entity
    entitiesComponentsIndex.at(entity)[componentType] = -1;

    // Check witch system should know about this entity
    unregisterEntity(entity, componentType);
}

void EntitiesManager::deleteEntity(unsigned int entity)
{
    // Delete all its components
    deleteAllComponentsFromEntity(entity);

    // Delete entity TODO
    // entity's components references are left in entitiesComponentsIndex...
}

unsigned int EntitiesManager::addPositionComponent()
{
    positionComponents.push_back(Component::Position());
    return unsigned(positionComponents.size());
}
unsigned int EntitiesManager::addVisibilityComponent()
{
    visibilityComponents.push_back(Component::Visibility());
    return unsigned(positionComponents.size());
}
unsigned int EntitiesManager::addLifeComponent()
{
    lifeComponents.push_back(Component::Life());
    return unsigned(positionComponents.size());
}

void EntitiesManager::deletePositionComponent(unsigned int index)
{
    positionComponents.erase(positionComponents.begin() + index);
}
void EntitiesManager::deleteVisibilityComponent(unsigned int index)
{
    visibilityComponents.erase(visibilityComponents.begin() + index);
}
void EntitiesManager::deleteLifeComponent(unsigned int index)
{
    lifeComponents.erase(lifeComponents.begin() + index);
}

void EntitiesManager::deleteComponent(Component::Type componentType, unsigned int index)
{
    switch (componentType)
    {
        // TODO use template
        case Component::Type::position: deletePositionComponent(index); break;
        case Component::Type::visibility: deleteVisibilityComponent(index); break;
        case Component::Type::life: deleteLifeComponent(index); break;
    }
}
void EntitiesManager::deleteAllComponentsFromEntity(unsigned int entity)
{
    for (auto i : entitiesComponentsIndex.at(entity))
    {
        if (i != -1)
        {
            deleteComponentFromEntity(entity, Component::Type(i));
        }
    }
}

void EntitiesManager::registerEntity(unsigned int entity, Component::Type componentType)
{
    for (auto s : systems)
    {
        if (s->hasComponentType(componentType))
        {
            s->registerEntity(entity);
        }
    }
}
void EntitiesManager::unregisterEntity(unsigned int entity, Component::Type componentType)
{
    for (auto s : systems)
    {
        if (s->hasComponentType(componentType))
        {
            s->unregisterEntity(entity);
        }
    }
}
