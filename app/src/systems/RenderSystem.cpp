#include "RenderSystem.hpp"
#include "utils/Log.hpp"
#include "ecs/ComponentManager.hpp"
#include "graphic/MeshFactory.hpp"
#include "graphic/Mesh.hpp"
#include "ecs/Id.hpp"
#include <fstream>
#include <math.h>

using namespace std;
using namespace Log;

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
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    loadShaderFile(vertexShader, "app/res/shaders/vertex_shader.vert");
    compileShader(vertexShader, shaderProgram);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    loadShaderFile(fragmentShader, "app/res/shaders/fragment_shader.frag");
    compileShader(fragmentShader, shaderProgram);

    linkProgram(shaderProgram);

    shaderW = glGetUniformLocation(shaderProgram, "W");
    shaderWVP = glGetUniformLocation(shaderProgram, "WVP");
    shaderTextureUnit = glGetUniformLocation(shaderProgram, "textureUnit");
    shaderLightColor = glGetUniformLocation(shaderProgram, "light.color");
    shaderLightAmbientIntensity = glGetUniformLocation(shaderProgram, "light.ambientIntensity");
    shaderLightDiffuseIntensity = glGetUniformLocation(shaderProgram, "light.diffuseIntensity");
    shaderLightDirection = glGetUniformLocation(shaderProgram, "light.direction");

    glDetachShader(shaderProgram, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(fragmentShader);

    perspective = glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.f);
    viewTranslation = glm::translate(viewTranslation, glm::vec3(0.f, -1.5f, -1.f));
    viewRotation = glm::rotate(viewRotation, float(M_PI / -2.f), glm::vec3(1.0f, 0.0f, 0.0f));
    viewRotation = glm::rotate(viewRotation, float(M_PI), glm::vec3(0.0f, 0.0f, 1.0f));
}

void RenderSystem::update()
{
    ECS::id entity;
    Movement* movement;
    Visibility* visibility;

    setGLStates();
    glUseProgram(shaderProgram);
    glUniform1i(shaderTextureUnit, 0);
    glUniform3f(shaderLightColor, 1.0, 0.9, 0.7);
    glUniform3f(shaderLightDirection, 0.0, -1.0, 1.0);
    glUniform1f(shaderLightAmbientIntensity, 0.2);
    glUniform1f(shaderLightDiffuseIntensity, 1.0);


    c += 0.01;

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        entity = getEntities()->at(i);

        if (visibilityComponents->hasComponent(entity)) {
            visibility = visibilityComponents->getComponent(entity);

            modelScale = glm::scale(glm::mat4(1.0f), visibility->scale);

            if (movementComponents->hasComponent(entity)) {
                movement = movementComponents->getComponent(entity);

                modelTranslation = glm::translate(glm::mat4(1.0f), movement->position);

                modelRotation = glm::mat4(0.1f);
                modelRotation = glm::rotate(modelRotation, movement->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
                modelRotation = glm::rotate(modelRotation, movement->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
                modelRotation = glm::rotate(modelRotation, movement->rotation.z - c, glm::vec3(0.0f, 0.0f, 1.0f));
            }

            Wprojection = modelRotation * modelScale;
            WVPprojection = perspective * viewRotation * viewTranslation * modelTranslation * modelRotation * modelScale;

            glUniformMatrix4fv(shaderW, 1, GL_FALSE, &Wprojection[0][0]);
            glUniformMatrix4fv(shaderWVP, 1, GL_FALSE, &WVPprojection[0][0]);

            meshFactory->getMesh(visibility->meshType)->draw();
        }
    }

    unsetGLStates();
}

void RenderSystem::setGLStates()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

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

void RenderSystem::compileShader(GLuint& shader, GLuint& program)
{
    GLint success;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == 0) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shader, sizeof(InfoLog), NULL, InfoLog);
        printl(InfoLog);
    } else {
        glAttachShader(program, shader);
    }
}

void RenderSystem::linkProgram(GLuint& program)
{
    GLint success;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == 0) {
        GLchar ErrorLog[1024];
        glGetProgramInfoLog(program, sizeof(ErrorLog), NULL, ErrorLog);
        printl(ErrorLog);
    } else {
        glValidateProgram(program);
    }
}
