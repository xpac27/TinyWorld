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
    light.direction = normalize(vec3(1.f, 1.f, -1.f));
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
    initializeShader(filling, "app/res/shaders/filling.vs", "app/res/shaders/filling.fs");

    renderingShaderTextureUnit = rendering.getLocation("textureUnit");
    renderingShaderLightColor = rendering.getLocation("light.color");
    renderingShaderLightAmbientIntensity = rendering.getLocation("light.ambientIntensity");
    renderingShaderLightDiffuseIntensity = rendering.getLocation("light.diffuseIntensity");
    renderingShaderLightDirection = rendering.getLocation("light.direction");
    renderingShaderSpecularIntensity = rendering.getLocation("specularIntensity");
    renderingShaderSpecularPower = rendering.getLocation("specularPower");
    renderingShaderEyeWorldPosition = rendering.getLocation("eyeWorldPosition");
    shadowingShaderLight = shadowing.getLocation("light");
    shadowingShaderWVP = shadowing.getLocation("WVP");
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
                // modelRotation = orientation(movement->direction, vec3(-1.0f, 0.0f, 0.0f));
                modelRotation = rotate(modelRotation, count, vec3(0.0f, 0.0f, 1.0f));
            }

            WVPprojections.add(visibility->meshType, eye.getPerspective() * eye.getRotation() * eye.getTranslation() * modelTranslation * modelRotation * modelScale);
            Wprojections.add(visibility->meshType, modelTranslation * modelRotation * modelScale);
            rotations.add(visibility->meshType, rotate(light.direction, count * -1, vec3(0.f, 0.f, 1.f)));
        }
    }

    uploadMatrices();

    // Culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

    // Render depth
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glClear(GL_DEPTH_BUFFER_BIT);
    depthPass();
    glDepthMask(GL_FALSE);

    // Render shadows
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_STENCIL_TEST_TWO_SIDE_EXT);
    glClear(GL_STENCIL_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    // glDisable(GL_CULL_FACE);

    // glActiveStencilFaceEXT(GL_FRONT);
    // glStencilMask(~0);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_INCR_WRAP_EXT);
    // glStencilFunc(GL_ALWAYS, 0, ~0);
    //
    // glActiveStencilFaceEXT(GL_BACK);
    // glStencilMask(~0);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_DECR_WRAP_EXT);
    // glStencilFunc(GL_ALWAYS, 0, ~0);

    // glActiveStencilFaceEXT(GL_FRONT);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_INCR_WRAP_EXT);
    // glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFFL);
    //
    // glActiveStencilFaceEXT(GL_BACK);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_DECR_WRAP_EXT);
    // glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFFL);

    // shadowPass();
    // glDisable(GL_STENCIL_TEST_TWO_SIDE_EXT);

    glDisable(GL_CULL_FACE);
    glStencilFunc(GL_ALWAYS, 0, 0);
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_KEEP,GL_INCR_WRAP);
    glStencilOpSeparate(GL_BACK ,GL_KEEP,GL_KEEP,GL_DECR_WRAP);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_FALSE);
    shadowPass();

        // glCullFace(GL_FRONT);
        // glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
        // shadowPass();
        //
        // glCullFace(GL_BACK);
        // glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
        // shadowPass();

    glEnable(GL_CULL_FACE);

    // Render scene
    glCullFace(GL_FRONT);
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glStencilFunc(GL_EQUAL, 0, 0xFFFFFFFFL);
    glDepthFunc(GL_LEQUAL);
    renderPass(eye.getPosition());
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    /*
    // Clear depth and color buffers
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_ONE, GL_ZERO); glEnable(GL_BLEND);
    glDepthMask(0xFF); glDepthFunc(GL_LEQUAL);
    depthPass();

    // Light passes
    glBlendFunc(GL_ONE, GL_ZERO);
    glDepthMask(0x00);
    glEnable(GL_STENCIL_TEST_TWO_SIDE_EXT);

    // Clear stencil buffer and switch to stencil-only rendering
    glClear(GL_STENCIL_BUFFER_BIT); glColorMask(0, 0, 0, 0);
    glDisable(GL_LIGHTING); glStencilFunc(GL_ALWAYS, 0, unsigned(~0));
    glStencilMask(unsigned(~0));

    glActiveStencilFaceEXT(GL_FRONT);
    glStencilOp(GL_KEEP, GL_DECR_WRAP_EXT, GL_KEEP);
    glActiveStencilFaceEXT(GL_BACK);
    glStencilOp(GL_KEEP, GL_INCR_WRAP_EXT, GL_KEEP);
    glCullFace(GL_NONE);
    shadowPass();

    glActiveStencilFaceEXT(GL_FRONT);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glActiveStencilFaceEXT(GL_BACK);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glDepthFunc(GL_EQUAL); glColorMask(1, 1, 1, 1);
    glCullFace(GL_BACK);

    renderPass(eye.getPosition());
    */

    WVPprojections.clear();
    Wprojections.clear();
    rotations.clear();

    count += 0.01;
}

void RenderSystem::uploadMatrices()
{
    for (unsigned int t = 0; t < WVPprojections.size(); t ++) {
        meshStore->getMesh(MeshType(t))->updateMatrices(WVPprojections.size(t), WVPprojections.get(t)->data(), Wprojections.get(t)->data());
    }
}

void RenderSystem::depthPass()
{
    filling.use();
    for (unsigned int t = 0; t < WVPprojections.size(); t ++) {
        meshStore->getMesh(MeshType(t))->bindIndexes();
        meshStore->getMesh(MeshType(t))->draw(WVPprojections.size(t));
    }
    filling.idle();
}

void RenderSystem::shadowPass()
{
    shadowing.use();
    for (unsigned int t = 0; t < rotations.size(); t ++) {
        for (unsigned int i = 0; i < rotations.size(t); i++) {
            glUniformMatrix4fv(shadowingShaderWVP, 1, GL_FALSE, &WVPprojections.get(t)->at(i)[0][0]);
            glUniform4f(shadowingShaderLight, rotations.get(t)->at(i).x, rotations.get(t)->at(i).y, rotations.get(t)->at(i).z, 0.f);

            meshStore->getMesh(MeshType(t))->updateShadowVolume(rotations.get(t)->at(i));
            meshStore->getMesh(MeshType(t))->bindSilhouette();
            meshStore->getMesh(MeshType(t))->drawShadowVolume();
        }
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
        meshStore->getMesh(MeshType(t))->bindIndexes();
        meshStore->getMesh(MeshType(t))->draw(WVPprojections.size(t));
    }
    rendering.idle();
}
