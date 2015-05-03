#include "Application.hpp"
#include <cmath>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "helpers/Debug.hpp"

void setupGLFW(GLFWwindow* window);
void setupGlew();
void setupOpenGL();
void glfwErrorCallback(int error, const char* description);
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    if (!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(glfwErrorCallback);

    GLFWwindow* window = glfwCreateWindow(640, 480, "TinyWorld", NULL, NULL);

    setupGLFW(window);
    setupGlew();
    setupOpenGL();

    srand(unsigned(time(NULL)));

    Application application;

    while (!glfwWindowShouldClose(window))
    {
        // application.update(0.0001f);
        // TODO draw every 1/60 seconds
        application.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void setupGLFW(GLFWwindow* window)
{
    if (window) {
        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, glfwKeyCallback);
    } else {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void setupGlew()
{
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK == err) {
        std::printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
    } else {
        std::fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }
}

void setupOpenGL()
{
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glClearDepth(GL_ONE);
    glClearStencil(GL_ZERO);
    glClearColor(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
}

void glfwErrorCallback(int /*error*/, const char* description)
{
    fputs(description, stderr);
}

void glfwKeyCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
