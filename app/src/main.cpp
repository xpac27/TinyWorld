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

    std::cout << std::endl;
    std::cout << "new entity #" << e1 << std::endl;
    std::cout << "new entity #" << e2 << std::endl;
    std::cout << "new entity #" << e3 << std::endl;

    std::cout << std::endl;
    std::cout << "total entities: " << entityManager.getEntityCount() << std::endl;

    entityManager.addComponentToEntity(e1, Component::Type::position);

    entityManager.addComponentToEntity(e2, Component::Type::position);
    entityManager.addComponentToEntity(e2, Component::Type::life);

    entityManager.addComponentToEntity(e3, Component::Type::position);
    entityManager.addComponentToEntity(e3, Component::Type::life);
    entityManager.addComponentToEntity(e3, Component::Type::visibility);

    std::cout << std::endl;
    std::cout << "entity #" << e1 << " has component position? " << (entityManager.hasComponent(Component::Type::position, e1) ? "yes" : "no") << std::endl;
    std::cout << "entity #" << e1 << " has component life? " << (entityManager.hasComponent(Component::Type::life, e1) ? "yes" : "no") << std::endl;
    std::cout << "entity #" << e1 << " has component visibility? " << (entityManager.hasComponent(Component::Type::visibility, e1) ? "yes" : "no") << std::endl;
    std::cout << std::endl;
    std::cout << "entity #" << e2 << " has component position? " << (entityManager.hasComponent(Component::Type::position, e2) ? "yes" : "no") << std::endl;
    std::cout << "entity #" << e2 << " has component life? " << (entityManager.hasComponent(Component::Type::life, e2) ? "yes" : "no") << std::endl;
    std::cout << "entity #" << e2 << " has component visibility? " << (entityManager.hasComponent(Component::Type::visibility, e2) ? "yes" : "no") << std::endl;
    std::cout << std::endl;
    std::cout << "entity #" << e3 << " has component position? " << (entityManager.hasComponent(Component::Type::position, e3) ? "yes" : "no") << std::endl;
    std::cout << "entity #" << e3 << " has component life? " << (entityManager.hasComponent(Component::Type::life, e3) ? "yes" : "no") << std::endl;
    std::cout << "entity #" << e3 << " has component visibility? " << (entityManager.hasComponent(Component::Type::visibility, e3) ? "yes" : "no") << std::endl;

    std::cout << std::endl;
    std::cout << "entity #" << e1 << ":" << std::endl;
    Component::debugPosition(entityManager.getPositionComponent(e1));

    std::cout << std::endl;
    std::cout << "entity #" << e2 << ":" << std::endl;
    Component::debugPosition(entityManager.getPositionComponent(e2));
    Component::debugLife(entityManager.getLifeComponent(e2));

    std::cout << std::endl;
    std::cout << "entity #" << e3 << ":" << std::endl;
    Component::debugPosition(entityManager.getPositionComponent(e3));
    Component::debugLife(entityManager.getLifeComponent(e3));
    Component::debugVisibility(entityManager.getVisibilityComponent(e3));
}

// --------------------------------------------------------------------------------- SYSTEM
void Component::debugPosition(Component::Position position)
{
    std::cout << "- Position (" << position.x << ", " << position.y << ")" << std::endl;
}
void Component::debugLife(Component::Life life)
{
    std::cout << "- Life (" << life.amount << ")" << std::endl;
}
void Component::debugVisibility(Component::Visibility visibility)
{
    std::cout << "- Visibility (" << (visibility.active ? "true" : "false") << ")" << std::endl;
}

// --------------------------------------------------------------------------------- SYSTEM
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"
#pragma clang diagnostic ignored "-Wreturn-type"
bool System::useComponent(Component::Type componentType) const
{
    switch (componentType)
    {
        // TODO use template
        case Component::Type::position: 
            return componentTypes & mask(as_int(Component::Type::position));
        case Component::Type::life: 
            return componentTypes & mask(as_int(Component::Type::life));
        case Component::Type::visibility: 
            return componentTypes & mask(as_int(Component::Type::visibility));
    }
}
#pragma clang diagnostic pop
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
    // TODO check MAX_UINT > entityCount
    entitiesComponentsIndex.push_back({{}});
    entitiesComponentsIndex.back().fill(UINT_MAX);
    return ++entityCount - 1;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"
void EntitiesManager::addComponentToEntity(unsigned int entity, Component::Type componentType)
{
    // Create a new component and register it
    switch (componentType)
    {
        // TODO use template
        case Component::Type::position: 
            registerComponent(Component::Type::position, entity, addPositionComponent()); 
            break;
        case Component::Type::life: 
            registerComponent(Component::Type::life, entity, addLifeComponent()); 
            break;
        case Component::Type::visibility: 
            registerComponent(Component::Type::visibility, entity, addVisibilityComponent()); 
            break;
    }

    // Check witch system should know about this entity
    registerEntity(entity, componentType);
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"
void EntitiesManager::deleteComponentFromEntity(unsigned int entity, Component::Type componentType)
{
    // Delete and unregister the component instance
    switch (componentType)
    {
        // TODO use template
        case Component::Type::position: 
            deletePositionComponent(entitiesComponentsIndex.at(entity).at(as_int(Component::Type::position))); 
            entitiesComponentsIndex.at(entity).at(as_int(Component::Type::position)) = UINT_MAX;
            break;
        case Component::Type::life: 
            deleteLifeComponent(entitiesComponentsIndex.at(entity).at(as_int(Component::Type::life))); 
            entitiesComponentsIndex.at(entity).at(as_int(Component::Type::life)) = UINT_MAX;
            break;
        case Component::Type::visibility: 
            deleteVisibilityComponent(entitiesComponentsIndex.at(entity).at(as_int(Component::Type::visibility))); 
            entitiesComponentsIndex.at(entity).at(as_int(Component::Type::visibility)) = UINT_MAX;
            break;
    }

    // Check witch system should know about this entity
    unregisterEntity(entity, componentType);
}
#pragma clang diagnostic pop

void EntitiesManager::resetEntity(unsigned int entity)
{
    // Delete all its components
    deleteAllComponentsFromEntity(entity);
}

bool EntitiesManager::hasComponent(Component::Type componentType, unsigned int entity) const 
{
    return entitiesComponentsIndex.at(entity).at(as_uint(componentType)) != UINT_MAX;
}


unsigned int EntitiesManager::getEntityCount() const
{
    return entityCount;
}

Component::Position EntitiesManager::getPositionComponent(unsigned int entity) const
{
    // TODO throw if component not avialable
    return positionComponents.at(entitiesComponentsIndex.at(entity).at(as_int(Component::Type::position)));
}
Component::Life EntitiesManager::getLifeComponent(unsigned int entity) const
{
    // TODO throw if component not avialable
    return lifeComponents.at(entitiesComponentsIndex.at(entity).at(as_int(Component::Type::life)));
}
Component::Visibility EntitiesManager::getVisibilityComponent(unsigned int entity) const
{
    // TODO throw if component not avialable
    return visibilityComponents.at(entitiesComponentsIndex.at(entity).at(as_int(Component::Type::visibility)));
}

unsigned int EntitiesManager::addPositionComponent()
{
    positionComponents.push_back(Component::Position());
    return unsigned(positionComponents.size()) - 1;
}
unsigned int EntitiesManager::addVisibilityComponent()
{
    visibilityComponents.push_back(Component::Visibility());
    return unsigned(visibilityComponents.size()) - 1;
}
unsigned int EntitiesManager::addLifeComponent()
{
    lifeComponents.push_back(Component::Life());
    return unsigned(lifeComponents.size()) - 1;
}

void EntitiesManager::registerComponent(Component::Type componentType, unsigned int entity, unsigned int componentIndex) 
{
    entitiesComponentsIndex.at(entity).at(as_uint(componentType)) = componentIndex;
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

void EntitiesManager::deleteAllComponentsFromEntity(unsigned int entity)
{
    for (auto i : entitiesComponentsIndex.at(entity))
    {
        if (i != UINT_MAX)
        {
            deleteComponentFromEntity(entity, Component::Type(i));
        }
    }
}

void EntitiesManager::registerEntity(unsigned int entity, Component::Type componentType)
{
    for (auto s : systems)
    {
        if (s->useComponent(componentType))
        {
            s->registerEntity(entity);
        }
    }
}
void EntitiesManager::unregisterEntity(unsigned int entity, Component::Type componentType)
{
    for (auto s : systems)
    {
        if (s->useComponent(componentType))
        {
            s->unregisterEntity(entity);
        }
    }
}
