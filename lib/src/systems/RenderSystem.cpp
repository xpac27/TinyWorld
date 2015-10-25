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

    Shader renderingVS(GL_VERTEX_SHADER, &rendering);
    renderingVS.read("app/res/shaders/rendering.vs");
    renderingVS.compile();

    Shader renderingFS(GL_FRAGMENT_SHADER, &rendering);
    renderingFS.read("app/res/shaders/rendering.fs");
    renderingFS.compile();

    Shader shadowingVS(GL_VERTEX_SHADER, &shadowing);
    shadowingVS.read("app/res/shaders/shadowing.vs");
    shadowingVS.compile();

    Shader shadowingFS(GL_FRAGMENT_SHADER, &shadowing);
    shadowingFS.read("app/res/shaders/shadowing.fs");
    shadowingFS.compile();

    Shader debugingVS(GL_VERTEX_SHADER, &debuging);
    debugingVS.read("app/res/shaders/debuging.vs");
    debugingVS.compile();

    Shader debugingFS(GL_FRAGMENT_SHADER, &debuging);
    debugingFS.read("app/res/shaders/debuging.fs");
    debugingFS.compile();

    rendering.link();
    shadowing.link();
    debuging.link();

    frameBuffer.initialize(100, 100);

    renderingTextureUnit = rendering.getLocation("textureUnit");
    renderingLightColor = rendering.getLocation("light.color");
    renderingLightAmbientIntensity = rendering.getLocation("light.ambientIntensity");
    renderingLightDiffuseIntensity = rendering.getLocation("light.diffuseIntensity");
    renderingLightDirection = rendering.getLocation("light.direction");
    renderingSpecularIntensity = rendering.getLocation("specularIntensity");
    renderingSpecularPower = rendering.getLocation("specularPower");
    renderingEyeWorldPosition = rendering.getLocation("eyePOVWorldPosition");
    debugingTextureUnit = debuging.getLocation("textureUnit");
}

void RenderSystem::update()
{
    Camera eyePOV(0.f, -3.f, 6.f, float(M_PI) / -5.f, 0.f, 0.f);
    Camera lightPOV(0.f, 0.f, 6.f, 0.f, 0.f, 0.f);

    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        id entity = getEntities()->at(i);

        if (visibilityComponents->hasComponent(entity)) {
            Visibility* visibility = visibilityComponents->getComponent(entity);

            mat4 modelRotation(1.0f);
            mat4 modelTranslation(1.0f);
            mat4 modelScale = scale(mat4(1.0f), visibility->scale);

            if (movementComponents->hasComponent(entity)) {
                Movement* movement = movementComponents->getComponent(entity);

                modelTranslation = translate(mat4(1.0f), movement->position);
                modelRotation = orientation(movement->direction, vec3(-1.0f, 0.0f, 0.0f));
                modelRotation = rotate(modelRotation, count, vec3(0.0f, 0.0f, 1.0f));
            }

            WVPEyeProjections.add(visibility->meshType, eyePOV.getPerspective() * eyePOV.getRotation() * eyePOV.getTranslation() * modelTranslation * modelRotation * modelScale);
            WVPLightProjections.add(visibility->meshType, lightPOV.getPerspective() * lightPOV.getRotation() * lightPOV.getTranslation() * modelTranslation * modelRotation * modelScale);
            Wprojections.add(visibility->meshType, modelTranslation * modelRotation * modelScale);
        }
    }

    setGLStates();
    shadowPass();
    renderPass(eyePOV.getPosition());
    debugPass();
    unsetGLStates();

    WVPEyeProjections.clear();
    WVPLightProjections.clear();
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

    glEnable(GL_TEXTURE_2D);

    glDepthMask(GL_TRUE);
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
}

void RenderSystem::unsetGLStates()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glDepthMask(GL_FALSE);
}

void RenderSystem::shadowPass()
{
    frameBuffer.bindForWriting();

    glClear(GL_DEPTH_BUFFER_BIT);

    shadowing.use();

    for (unsigned int t = 0; t < WVPLightProjections.size(); t ++) {
        meshStore->getMesh(MeshType(t))->draw(WVPLightProjections.size(t), WVPLightProjections.get(t)->data(), Wprojections.get(t)->data());
    }

    frameBuffer.idle();

    shadowing.idle();
}

void RenderSystem::renderPass(glm::vec3 POVPosition)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rendering.use();

    glUniform1i(renderingTextureUnit, 0);
    glUniform3f(renderingLightColor, light.color.x, light.color.y, light.color.z);
    glUniform3f(renderingLightDirection, light.direction.x, light.direction.y, light.direction.z);
    glUniform1f(renderingLightAmbientIntensity, light.ambientIntensity);
    glUniform1f(renderingLightDiffuseIntensity, light.diffuseIntensity);
    glUniform1f(renderingSpecularIntensity, 4.0);
    glUniform1f(renderingSpecularPower, 32.0);
    glUniform3f(renderingEyeWorldPosition, POVPosition.x, POVPosition.y, POVPosition.z);

    for (unsigned int t = 0; t < WVPEyeProjections.size(); t ++) {
        meshStore->getMesh(MeshType(t))->bindTexture();
        meshStore->getMesh(MeshType(t))->draw(WVPEyeProjections.size(t), WVPEyeProjections.get(t)->data(), Wprojections.get(t)->data());
    }

    rendering.idle();
}

void RenderSystem::debugPass()
{
    debuging.use();

    glUniform1i(debugingTextureUnit, 0);

    frameBuffer.bindForReading();

    mat4 m(1.0f);
    m = translate(m, glm::vec3(0, 0, -1));
    meshStore->getMesh(MeshType::PLAN)->draw(1, &m, &m);

    frameBuffer.idle();
    debuging.idle();
}
