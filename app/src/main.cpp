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

using namespace std;

namespace Type {
    struct A { const unsigned int id = 1; };
    struct B { const unsigned int id = 2; };
}

// template <typename T>
// struct Component {
//     static const unsigned int typeId = T().id;
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

class Factory
{
public:
    id addEntity();

    template<typename T>
    T* addComponent(id entity);
    template<typename T>
    T* getComponent(id entity);
    template<typename T>
    T* delComponent(id entity);

private:
    vector<array<id, 3>> entitiesComponents;

    template<typename T>
    vector<T>& list();
};

id Factory::addEntity()
{
    for (auto& e : entitiesComponents) {
       if (e[0] == 0) {
           return id(&e - &entitiesComponents[0]);
       }
    }
    entitiesComponents.push_back({{0, 0, 0}});
    return entitiesComponents.size() - 1;
}

template<typename T>
vector<T>& Factory::list()
{
    static vector<T> *l = new vector<T>();
    return *l;
}

template<typename T>
T* Factory::addComponent(id entity)
{
    list<T>().push_back(T());
    return &list<T>().back();
}

// template<typename T>
// T* Factory::getComponent(id entity)
// {
//     return &entitiesComponents.at(entity).at(T::typeId);
// }

int main()
{
    Factory f;

    id e1 = f.addEntity();
    id e2 = f.addEntity();

    A *e1a = f.addComponent<A>(e1);
    A *e2a = f.addComponent<A>(e2);
    B *e2b = f.addComponent<B>(e2);

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

