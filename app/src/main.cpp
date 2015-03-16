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

struct A {
    int a;
};

struct B {
    int b;
};

class Factory {
public:
    long addEntity();

private:
    vector<A> aComponents;
    vector<B> bComponents;
    vector<array<long, 3>> entitiesComponents;
};

long Factory::addEntity() {
    for (auto& e : entitiesComponents) {
       if (e[0] == 0) {
           return &e - &entitiesComponents[0];
       }
    }
    entitiesComponents.push_back({{0, 0, 0}});
    return long(entitiesComponents.size()) - 1;
}

int main()
{
    Factory f;
    long e1 = f.addEntity();
    long e2 = f.addEntity();
    cout << e1 << endl;
    cout << e2 << endl;
    return 0;
}
