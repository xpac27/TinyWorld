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
#include <glm/gtc/type_ptr.hpp>
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
    , camera(new Camera(0.f, -3.f, 8.f, float(M_PI) / -5.f, 0.f, 0.f))
{
    // TODO make this date driven
    light.color = vec3(1.0, 0.9, 0.7);
    light.direction = normalize(vec3(1.f, 1.f, -1.f));
    light.ambientIntensity = 0.2f;
    light.diffuseIntensity = 1.0f;
    light.intensity = 1.0f;
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
    initializeShader(geometryBuffer, "app/res/shaders/geometry_buffer.vs", "app/res/shaders/geometry_buffer.fs");
    initializeShader(deferredShading, "app/res/shaders/deferred_shading.vs", "app/res/shaders/deferred_shading.fs");

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

    // ----

    // TODO auto detect screen size
    int SCR_WIDTH = 800;
    int SCR_HEIGHT = 600;

    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    // - Position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    // - Normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    // - Color + Specular color buffer
    glGenTextures(1, &gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);

    // - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);

    // - Create and attach depth buffer (renderbuffer)
    GLuint rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    // - Finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer not complete!" << std::endl; // TODO proper error log
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // ----

    GLfloat quadVertices[] = {
        // Positions        // Texture Coords
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
    };
    // Setup plane VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
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

            // WVPprojections.add(visibility->meshType, eye.getPerspective() * eye.getRotation() * eye.getTranslation() * modelTranslation * modelRotation * modelScale);
            modelMatrices.add(visibility->meshType, modelTranslation * modelRotation * modelScale);
            rotations.add(visibility->meshType, rotate(light.direction, count * -1, vec3(0.f, 0.f, 1.f)));
        }
    }

    count += 0.01;

    uploadMatrices();
    // render(eye.getPosition());
    render2();

    WVPprojections.clear();
    Wprojections.clear();
    rotations.clear();
    modelMatrices.clear();
}

void RenderSystem::render2()
{
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glDepthFunc(GL_LEQUAL);

    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        geometryBuffer.use();

        glUniform1i(geometryBuffer.getLocation("texture_diffuse1"), 0);
        glUniform1i(geometryBuffer.getLocation("texture_specular1"), 1);
        glUniformMatrix4fv(geometryBuffer.getLocation("view"), 1, GL_FALSE, value_ptr(camera->getTranslation() * camera->getRotation()));
        glUniformMatrix4fv(geometryBuffer.getLocation("projection"), 1, GL_FALSE, value_ptr(camera->getPerspective()));

        for (unsigned int t = 0; t < modelMatrices.size(); t ++) {
            meshStore->getMesh(MeshType(t))->bindTexture();
            meshStore->getMesh(MeshType(t))->bindIndexes();
            meshStore->getMesh(MeshType(t))->draw(modelMatrices.size(t));
        }

        geometryBuffer.idle();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // ----

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    deferredShading.use();

    glUniform1i(deferredShading.getLocation("gPosition"), 0);
    glUniform1i(deferredShading.getLocation("gNormal"), 1);
    glUniform1i(deferredShading.getLocation("gAlbedoSpec"), 2);

    glUniform3f(deferredShading.getLocation("Light.color"), light.color.x, light.color.y, light.color.z);
    glUniform3f(deferredShading.getLocation("Light.direction"), light.direction.x, light.direction.y, light.direction.z);
    glUniform1f(deferredShading.getLocation("Light.intensity"), light.intensity);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);

    glUniformMatrix4fv(deferredShading.getLocation("viewPos"), 1, GL_FALSE, value_ptr(camera->getPosition()));

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    deferredShading.idle();
}

void RenderSystem::render(vec3 eyePosition)
{
    // Settings
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

    // Render depth
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);
    depthPass();
    glDepthMask(GL_FALSE);

    // Render shadows
    glDisable(GL_CULL_FACE);
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFFL);
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_KEEP,GL_INCR_WRAP);
    glStencilOpSeparate(GL_BACK ,GL_KEEP,GL_KEEP,GL_DECR_WRAP);
    glDepthFunc(GL_LESS);
    shadowPass();
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    // Render scene
    glEnable(GL_CULL_FACE);
    glStencilFunc(GL_EQUAL, 0, 0xFFFFFFFFL);
    glDepthFunc(GL_LEQUAL);
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT);
    colorPass(eyePosition);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void RenderSystem::uploadMatrices()
{
    for (unsigned int t = 0; t < modelMatrices.size(); t ++) {
        meshStore->getMesh(MeshType(t))->updateMatrices(modelMatrices.size(t), modelMatrices.get(t)->data());
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

void RenderSystem::colorPass(glm::vec3 eyePosition)
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
