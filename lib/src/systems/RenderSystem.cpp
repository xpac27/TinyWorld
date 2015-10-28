#include "systems/RenderSystem.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/Id.hpp"
#include "utils/Log.hpp"
#include "utils/Shader.hpp"
#include "graphic/MeshStore.hpp"
#include "graphic/Mesh.hpp"
#include "graphic/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <math.h>

using namespace std;
using namespace glm;
using namespace Log;
using namespace ECS;

RenderSystem::RenderSystem(
    ComponentManager<Visibility>* vc,
    ComponentManager<Movement>* mc
)
    : System({vc, mc})
    , visibilityComponents(vc)
    , movementComponents(mc)
    , meshStore(new MeshStore())
{
    // TODO make this date driven
    light.color = vec3(1.0, 0.9, 0.7);
    light.direction = normalize(vec3(1.f, 1.f, -1.0f));
    light.ambientIntensity = 0.2f;
    light.diffuseIntensity = 1.0f;
}

RenderSystem::~RenderSystem()
{
    delete meshStore;
}

void RenderSystem::initialize()
{
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    initializeShader(rendering, "app/res/shaders/rendering.vs", "app/res/shaders/rendering.fs");
    initializeShader(shadowing, "app/res/shaders/shadowing.vs", "app/res/shaders/shadowing.fs");

    renderingShaderTextureUnit = rendering.getLocation("textureUnit");
    renderingShaderLightColor = rendering.getLocation("light.color");
    renderingShaderLightAmbientIntensity = rendering.getLocation("light.ambientIntensity");
    renderingShaderLightDiffuseIntensity = rendering.getLocation("light.diffuseIntensity");
    renderingShaderLightDirection = rendering.getLocation("light.direction");
    renderingShaderSpecularIntensity = rendering.getLocation("specularIntensity");
    renderingShaderSpecularPower = rendering.getLocation("specularPower");
    renderingShaderEyeWorldPosition = rendering.getLocation("eyeWorldPosition");
}

void RenderSystem::initializeShader(Program &program, const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
{
    Shader renderingVertexShader(GL_VERTEX_SHADER, &program);
    renderingVertexShader.read(vertexShaderFilePath);
    renderingVertexShader.compile();

    Shader renderingFragmentShader(GL_FRAGMENT_SHADER, &program);
    renderingFragmentShader.read(fragmentShaderFilePath);
    renderingFragmentShader.compile();

    program.link();
}

void RenderSystem::update()
{
    Camera eye(0.f, -3.f, 6.f, float(M_PI) / -5.f, 0.f, 0.f);

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        id entity = getEntities()->at(i);

        if (visibilityComponents->hasComponent(entity)) {
            Visibility* visibility = visibilityComponents->getComponent(entity);

            mat4 modelRotation;
            mat4 modelTranslation;
            mat4 modelScale = scale(mat4(1.0f), visibility->scale);

            if (movementComponents->hasComponent(entity)) {
                Movement* movement = movementComponents->getComponent(entity);

                modelTranslation = translate(mat4(1.0f), movement->position);
                modelRotation = orientation(movement->direction, vec3(-1.0f, 0.0f, 0.0f));
                modelRotation = rotate(modelRotation, count, vec3(0.0f, 0.0f, 1.0f));
            }

            WVPprojections.add(visibility->meshType, eye.getPerspective() * eye.getRotation() * eye.getTranslation() * modelTranslation * modelRotation * modelScale);
            Wprojections.add(visibility->meshType, modelTranslation * modelRotation * modelScale);
        }
    }

    setGLStates();
    shadowPass();
    renderPass(eye.getPosition());
    unsetGLStates();

    WVPprojections.clear();
    Wprojections.clear();

    count += 0.03;
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

void RenderSystem::shadowPass()
{
    shadowing.use();
    vec3 dir(1, 1 ,1);

    for (unsigned int t = 0; t < WVPprojections.size(); t ++) {
        meshStore->getMesh(MeshType(t))->updateShadowVolume(dir);
        meshStore->getMesh(MeshType(t))->updateMatrices(WVPprojections.size(t), WVPprojections.get(t)->data(), Wprojections.get(t)->data());
        meshStore->getMesh(MeshType(t))->drawShadowVolume(WVPprojections.size(t));
    }

    shadowing.idle();
}

void RenderSystem::renderPass(glm::vec3 eyePosition)
{
    rendering.use();
    glUniform1i(renderingShaderTextureUnit, 0);
    glUniform3f(renderingShaderLightColor, light.color.x, light.color.y, light.color.z);
    glUniform3f(renderingShaderLightDirection, light.direction.x, light.direction.y, light.direction.z);
    glUniform1f(renderingShaderLightAmbientIntensity, light.ambientIntensity);
    glUniform1f(renderingShaderLightDiffuseIntensity, light.diffuseIntensity);
    glUniform1f(renderingShaderSpecularIntensity, 4.0);
    glUniform1f(renderingShaderSpecularPower, 32.0);
    glUniform3f(renderingShaderEyeWorldPosition, eyePosition.x, eyePosition.y, eyePosition.z);

    for (unsigned int t = 0; t < WVPprojections.size(); t ++) {
        meshStore->getMesh(MeshType(t))->bindTexture();
        meshStore->getMesh(MeshType(t))->updateMatrices(WVPprojections.size(t), WVPprojections.get(t)->data(), Wprojections.get(t)->data());
        meshStore->getMesh(MeshType(t))->draw(WVPprojections.size(t));
    }

    rendering.idle();
}
