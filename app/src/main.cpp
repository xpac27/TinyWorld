// #include "main.hpp"

// #include "Application.hpp"

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
//     while (window.isOpen()) {
//         if (Keyboard::isKeyPressed(Keyboard::Escape))
//             window.close();
//
//         Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == Event::Closed) window.close();
//             if (event.type == Event::Resized) setupWindow(event.size.width, event.size.height);
//         }
//
//         glLoadIdentity();
//         application.update(clock.getElapsedTime().asSeconds());
//         application.draw();
//         window.display();
//         clock.restart();
//     }
//
//     return 0;
// }
//
// void setupWindow(unsigned int width, unsigned int height)
// {
//     float sceneWidth = 4.f;
//     float sceneHeight = 3.f;
//     if (width > height) {
//         sceneWidth = 100.f;
//         sceneHeight = 100.f * (height / width);
//     } else if (width < height) {
//         sceneWidth = 100.f * (width / height);
//         sceneHeight = 100.f;
//     } else {
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
#include <vector>
#include <string>

using namespace std;

struct A
{
    int a = 0;
};

struct B
{
    int b = 0;
};

typedef size_t id;

template <typename T>
class ComponentManager
{
public:
    T& createComponent();
    T& getComponent(id entity);
    void addComponent(T &component, id entity);
    void delComponent(id entity);
    bool hasComponent(id entity);
private:
    vector<T> components {};
    vector<T*> entitiesComponents {};
};

class EntityManager
{
public:
    id addEntity();
private:
    unsigned int totalEntities = 0;
};

int main()
{
    EntityManager e;
    id e1 = e.addEntity();
    id e2 = e.addEntity();

    ComponentManager<A> a = ComponentManager<A>();
    ComponentManager<B> b = ComponentManager<B>();
    A a1 = a.createComponent();
    A a2 = a.createComponent();
    B b1 = b.createComponent();
    a.addComponent(a1, e1);
    a.addComponent(a2, e2);
    b.addComponent(b1, e2);

    a1.a = 5;
    a2.a = 7;
    b1.b = 9;

    cout << e1 << " (" << a1.a << ")" << endl;
    cout << e2 << " (" << a2.a << "," << b1.b << ")" << endl;

    return 0;
}

template <typename T>
T& ComponentManager<T>::createComponent()
{
    components.push_back(T());
    return components.back();
}
template <typename T>
T& ComponentManager<T>::getComponent(id entity)
{
    return entitiesComponents.at(entity);
}
template <typename T>
void ComponentManager<T>::addComponent(T &component, id entity)
{
    if (entitiesComponents.size() <= entity) {
        entitiesComponents.resize(entity + 1, nullptr);
    }
    entitiesComponents.at(entity) = &component;
}
template <typename T>
void ComponentManager<T>::delComponent(id entity)
{
    delete entitiesComponents.at(entity); // is that nessecary?
    components.erase(entitiesComponents.at(entity)); // this wont work
    entitiesComponents.at(entity) = nullptr;
}
template <typename T>
bool ComponentManager<T>::hasComponent(id entity)
{
    return entity < entitiesComponents.size() && entitiesComponents.at(entity);
}

id EntityManager::addEntity()
{
    return ++totalEntities - 1;
}
