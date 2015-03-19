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
#include <array>
#include <string>

using namespace std;

// namespace Type {
//     struct A { const unsigned int id = 1; };
//     struct B { const unsigned int id = 2; };
// }

// template <typename T>
// struct Component {
//     static crnst unsigned int typeId = T().id;
// };
// template <typename T>
// struct Container {
//     static vector<T>& list()
//     {
//           static vector<T>* l = new vector<T>();
//           return *l;
//     }
// };

struct A
{
    int a = 0;
};

struct B
{
    int b = 0;
};

typedef size_t id;

class Identity
{
public:
    Identity(string name);
    string GetName();
private:
    string name;
};

template <typename T>
class ComponentManager : public Identity
{
public:
    T* addComponent(id entity);
    T* getComponent(id entity);
    T* delComponent(id entity);
private:
    vector<T> laura;
};

class ComponentManagers
{
public:
    template <typename T>
    ComponentManager<T>* CreateComponentManager(string name);
    template <typename T>
    ComponentManager<T>* GetComponentManager(string name);
private:
    vector<Identity*> randy;
};

class World
{
public:
    id addEntity();
    ComponentManagers& GetComponentManagers();
private:
    ComponentManagers componentsManagers;
    vector<array<id, 3>> entitiesComponents;
};

id World::addEntity()
{
    for (auto& e : entitiesComponents) {
       if (e[0] == 0) {
           return id(&e - &entitiesComponents[0]);
       }
    }
    entitiesComponents.push_back({{0, 0, 0}});
    return entitiesComponents.size() - 1;
}


int main()
{
    World w;

    id e1 = w.addEntity();
    id e2 = w.addEntity();

    ComponentManager<A> *a = w.GetComponentManagers().CreateComponentManager<A>("A");
    ComponentManager<B> *b = w.GetComponentManagers().CreateComponentManager<B>("B");

    A *e1a = a->addComponent(e1);
    A *e2a = a->addComponent(e2);
    B *e2b = b->addComponent(e2);

    cout << e1a << endl;
    cout << e2a << endl;
    cout << e2b << endl;

    e1a->a = 5;
    e2a->a = 7;
    e2b->b = 9;

    cout << e1 << " (" << e1a->a << ")" << endl;
    cout << e2 << " (" << e2a->a << "," << e2b->b << ")" << endl;

    return 0;
}

