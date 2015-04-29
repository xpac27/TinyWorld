#include "RenderSystem.hpp"
#include "helpers/Debug.hpp"
#include "ecs/ComponentManager.hpp"
#include "graphic/Vertex.hpp"
#include "graphic/MeshFactory.hpp"
#include "graphic/Mesh.hpp"
#include "ecs/Id.hpp"
#include <fstream>

using namespace std;

RenderSystem::RenderSystem(
    ECS::ComponentManager<Visibility>* vc,
    ECS::ComponentManager<Movement>* mc
)
    : System({vc, mc})
    , meshFactory(new MeshFactory())
    , visibilityComponents(vc)
    , movementComponents(mc)
{}

void RenderSystem::initialize()
{
    GLuint shaderProgram = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    loadShaderFile(vertexShader, "app/res/shaders/vertex_shader.vert");
    compileShader(vertexShader, shaderProgram);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    loadShaderFile(fragmentShader, "app/res/shaders/fragment_shader.frag");
    compileShader(fragmentShader, shaderProgram);

    linkProgram(shaderProgram);

    glDetachShader(shaderProgram, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);
}

void RenderSystem::update()
{
    ECS::id entity;
    Movement* movement;
    Visibility* visibility;

    setGLStates();
    glPushMatrix();
    glTranslatef(0.f, 0.f, -50.f);

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        entity = getEntities()->at(i);

        if (visibilityComponents->hasComponent(entity)) {
            visibility = visibilityComponents->getComponent(entity);

            glPushMatrix();

            if (movementComponents->hasComponent(entity)) {
                movement = movementComponents->getComponent(entity);
                glTranslatef(movement->position.x, movement->position.y, 0.f);
            }

            meshFactory->getMesh(visibility->meshType)->draw();

            glPopMatrix();
        }
    }

    glPopMatrix();
    unsetGLStates();
}

void RenderSystem::setGLStates()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.8f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.004f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.00005f);

    if (GLEW_ARB_vertex_buffer_object)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
    }

    glDepthMask(GL_TRUE);
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::unsetGLStates()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glDepthMask(GL_FALSE);
}

void RenderSystem::loadShaderFile(GLuint& shader, const char* filename)
{
    ifstream file(filename);
    std::string content, line = "";
    while(!file.eof()) {
        std::getline(file, line);
        content.append(line + "\n");
    }

    const GLchar* p[1] = {content.data()};
    GLint l[1] = {GLint(content.size())};

    glShaderSource(shader, 1, p, l);
}

bool RenderSystem::compileShader(GLuint& shader, GLuint& program)
{
    GLint success;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shader, sizeof(InfoLog), NULL, InfoLog);
        Debug::print(InfoLog);
        return false;
    } else {
        glAttachShader(program, shader);
    }
    return true;
}

bool RenderSystem::linkProgram(GLuint& program)
{
    GLint success;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == 0) {
        GLchar ErrorLog[1024];
        glGetProgramInfoLog(program, sizeof(ErrorLog), NULL, ErrorLog);
        Debug::print(ErrorLog);
        return false;
    } else {
        glValidateProgram(program);
    }
    return true;
}
