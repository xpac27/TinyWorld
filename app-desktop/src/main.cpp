#include <GLFW/glfw3.h>

#include <Application.hpp>

#include <cmath>
#include <ctime>
#include <thread>
#include <cstdio>
#include <stdlib.h>

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

    printf("GL Version %s\n", glGetString(GL_VERSION));

    // Random seed
    srand(unsigned(time(NULL)));

    // Initialize application
    application = new Application();
    application->setup({
        .rootPath = "lib"
    });

    // Create a draw and update thread
    thread t1(draw, application, window);

    // Run the app
    while (application->isRunning() && !glfwWindowShouldClose(window)) glfwPollEvents();

    // Wait for threads
    t1.join();

    // GLFW shutdown
    glfwSetWindowShouldClose(window, GL_TRUE);
	glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// ================================

void draw(Application *app, GLFWwindow *window)
{
    glfwMakeContextCurrent(window);

    while (app->isRunning()) {
        app->update(float(glfwGetTime()));
        app->draw();
        glfwSwapBuffers(window);
    }
}

// --------------------------------

void glfwErrorCallback(int /*error*/, const char* description)
{
    fputs(description, stderr);
}

void glfwKeyCallback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
{
    switch (action) {
        case GLFW_PRESS: application->onKeyPressed(key);
    }
}
