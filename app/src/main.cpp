#include "Application.hpp"
#include <cmath>
#include <ctime>
#include <thread>
#include <cstdio>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void glfwErrorCallback(int error, const char* description);
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void draw(Application *application, GLFWwindow *window);
void update(Application *application);

static Application *application;

int main()
{
    // GLFW initialize
    if (glfwInit()){
        glfwWindowHint(GLFW_SAMPLES, 0);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwSetErrorCallback(glfwErrorCallback);
    } else {
        exit(EXIT_FAILURE);
    }

    // GLFW create context window
    GLFWwindow* window = glfwCreateWindow(800, 600, "TinyWorld", NULL, NULL);
    if (window) {
        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, glfwKeyCallback);
        glfwSwapInterval(1);
    } else {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // GLEW initialize
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK == err) {
        printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
    } else {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Random seed
    srand(unsigned(time(NULL)));

    // Initialize application
    application = new Application();

    // Create a draw and update thread
    thread t1(update, application);
    thread t2(draw, application, window);

    // Run the app
    while (application->isRunning()) glfwPollEvents();

    // Wait for threads
    t1.join();
    t2.join();

    // GLFW shutdown
    glfwSetWindowShouldClose(window, GL_TRUE);
    glfwTerminate();

    return 0;
}

// ================================

void draw(Application *app, GLFWwindow *window)
{
    glfwMakeContextCurrent(window);

    while (app->isRunning()) {
        app->draw();
        glfwSwapBuffers(window);
    }
}

void update(Application *app)
{
    while (app->isRunning()) {
        app->update(float(glfwGetTime()));
    }
}

// --------------------------------

void glfwErrorCallback(int /*error*/, const char* description)
{
    fputs(description, stderr);
}

void glfwKeyCallback(GLFWwindow* /*window*/, int key, int scancode, int action, int mods)
{
    application->keyCallback(key, scancode, action, mods);
}
