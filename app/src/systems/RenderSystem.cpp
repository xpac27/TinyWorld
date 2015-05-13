#include "RenderSystem.hpp"
#include "utils/Log.hpp"
#include "utils/Shader.hpp"
#include "utils/Program.hpp"
#include "ecs/ComponentManager.hpp"
#include "graphic/MeshStore.hpp"
#include "graphic/Mesh.hpp"
#include "graphic/DirectionalLight.hpp"
#include "ecs/Id.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <math.h>

using namespace std;
using namespace glm;
using namespace Log;

RenderSystem::RenderSystem(
    ECS::ComponentManager<Visibility>* vc,
    ECS::ComponentManager<Movement>* mc
)
    : System({vc, mc})
    , meshStore(new MeshStore())
    , light(new DirectionalLight(vec3(1.0, 0.9, 0.7), normalize(vec3(1.f, 1.f, -1.0f)), 0.2f, 1.0f))
    , program(new Program())
    , eyePosition(0.f, -6.f, 10.f)
    , eyeRotation(float(M_PI) / -6.f, 0.f, 0.f)
    , visibilityComponents(vc)
    , movementComponents(mc)
{}

void RenderSystem::initialize()
{
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    Shader vertexShader(GL_VERTEX_SHADER, program);
    vertexShader.read("app/res/shaders/vertex_shader.vert");
    vertexShader.compile();

    Shader fragmentShader(GL_FRAGMENT_SHADER, program);
    fragmentShader.read("app/res/shaders/fragment_shader.frag");
    fragmentShader.compile();

    program->link();

    shaderW = program->getLocation("W");
    shaderWVP = program->getLocation("WVP");
    shaderTextureUnit = program->getLocation("textureUnit");
    shaderLightColor = program->getLocation("light.color");
    shaderLightAmbientIntensity = program->getLocation("light.ambientIntensity");
    shaderLightDiffuseIntensity = program->getLocation("light.diffuseIntensity");
    shaderLightDirection = program->getLocation("light.direction");
    shaderSpecularIntensity = program->getLocation("specularIntensity");
    shaderSpecularPower = program->getLocation("specularPower");
    shaderEyeWorldPosition = program->getLocation("eyeWorldPosition");
}

void RenderSystem::update()
{
    ECS::id entity;
    Movement* movement;
    Visibility* visibility;

    setGLStates();
    program->use();
    glUniform1i(shaderTextureUnit, 0);
    glUniform3f(shaderLightColor, light->color.x, light->color.y, light->color.z);
    glUniform3f(shaderLightDirection, light->direction.x, light->direction.y, light->direction.z);
    glUniform1f(shaderLightAmbientIntensity, light->ambientIntensity);
    glUniform1f(shaderLightDiffuseIntensity, light->diffuseIntensity);
    glUniform1f(shaderSpecularIntensity, 4.0);
    glUniform1f(shaderSpecularPower, 32.0);
    glUniform3f(shaderEyeWorldPosition, eyePosition.x, eyePosition.y, eyePosition.z);

    viewTranslation = translate(mat4(1.0f), eyePosition * -1.f);

    viewRotation = mat4(1.0f);
    viewRotation = rotate(viewRotation, eyeRotation.x, vec3(1.0f, 0.0f, 0.0f));
    viewRotation = rotate(viewRotation, eyeRotation.y, vec3(0.0f, 0.0f, 1.0f));
    viewRotation = rotate(viewRotation, eyeRotation.z, vec3(0.0f, 0.0f, 1.0f));

    // TODO use constants for screen size
    perspective = glm::perspective(float(M_PI) / 2.f, 4.f / 3.f, 0.1f, 100.f);

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        entity = getEntities()->at(i);

        if (visibilityComponents->hasComponent(entity)) {
            visibility = visibilityComponents->getComponent(entity);

            modelScale = scale(mat4(1.0f), visibility->scale);

            if (movementComponents->hasComponent(entity)) {
                movement = movementComponents->getComponent(entity);

                modelTranslation = translate(mat4(1.0f), movement->position);
                modelRotation = orientation(movement->direction, vec3(-1.0f, 0.0f, 0.0f));
            }

            Wprojection = modelRotation * modelScale;
            WVPprojection = perspective * viewRotation * viewTranslation * modelTranslation * modelRotation * modelScale;

            glUniformMatrix4fv(shaderW, 1, GL_FALSE, &Wprojection[0][0]);
            glUniformMatrix4fv(shaderWVP, 1, GL_FALSE, &WVPprojection[0][0]);

            meshStore->getMesh(visibility->meshType)->draw();
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
