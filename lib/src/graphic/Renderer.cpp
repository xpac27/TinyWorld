#include "Renderer.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "../utils/Shader.hpp"
#include "../utils/Log.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <GL/glew.h>

using namespace std;
using namespace glm;
using namespace Log;

Renderer::Renderer()
    : camera(new Camera(0.f, -5.f, 5.f, float(M_PI) * -0.25f, 0.f, 0.f))
{
    // TODO make this date driven
    directionalLight.color = vec3(0.7, 0.6, 0.5);
    directionalLight.direction = normalize(vec4(1.f, 1.f, -1.f, 0.f));

    cubemap.load({
        "textures/skybox/right.png",
        "textures/skybox/left.png",
        "textures/skybox/top.png",
        "textures/skybox/bottom.png",
        "textures/skybox/back.png",
        "textures/skybox/front.png",
    });
}

Renderer::~Renderer()
{
    delete camera;
}

void Renderer::reload()
{
    initializeShaders();
}

void Renderer::initialize()
{
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

    initializeShaders();

    quad.initialize();
    gBuffer.initialize();
}

void Renderer::initializeShaders()
{
    initializeShader(shadowVolume, "lib/src/shaders/shadow_volume.vs", "lib/src/shaders/shadow_volume.fs");
    initializeShader(filling, "lib/src/shaders/filling.vs", "lib/src/shaders/filling.fs");
    initializeShader(geometryBuffer, "lib/src/shaders/geometry_buffer.vs", "lib/src/shaders/geometry_buffer.fs");
    initializeShader(deferredShading, "lib/src/shaders/deferred_shading.vs", "lib/src/shaders/deferred_shading.fs");
    success("Shaders loaded");
}

void Renderer::initializeShader(Program &program, const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
{

    Shader vertexShader(GL_VERTEX_SHADER, &program);
    vertexShader.read(vertexShaderFilePath);
    vertexShader.compile();

    Shader fragmentShader(GL_FRAGMENT_SHADER, &program);
    fragmentShader.read(fragmentShaderFilePath);
    fragmentShader.compile();

    program.link();
}

void Renderer::render(Aggregator<Model> &models)
{
    uploadMatrices(models);

    // Off screen rendering
    gBuffer.bind();

    // Render depth
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);

    depthPass(models);;

    // Render shadows
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFFL);
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_KEEP,GL_INCR_WRAP);
    glStencilOpSeparate(GL_BACK ,GL_KEEP,GL_KEEP,GL_DECR_WRAP);
    glDepthFunc(GL_LESS);

    shadowPass(models);

    // Render scene
    glEnable(GL_CULL_FACE);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glStencilFunc(GL_EQUAL, 0, 0xFFFFFFFFL);
    glDepthFunc(GL_LEQUAL);
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT);

    geometryPass(models);

    // On screen rendering
    gBuffer.idle();

    // Render lighting
    glDepthMask(GL_TRUE);
    glDisable(GL_STENCIL_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lightingPass();

    // Reset states
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void Renderer::uploadMatrices(Aggregator<Model> &models)
{
    for (unsigned int t = 0; t < models.size(); t ++) {
        unsigned int totalModels = models.size(t);
        vector<mat4> matrices;
        matrices.reserve(models.size(t));
        for (unsigned int i = 0; i < totalModels; i++) {
            matrices.push_back(models.get(t)->at(i).getProduct());
        }
        meshStore.getMesh(MeshType(t))->updateMatrices(totalModels, matrices.data());
    }
}

void Renderer::depthPass(Aggregator<Model> &models)
{
    filling.use();

    glUniformMatrix4fv(filling.getLocation("view"), 1, GL_FALSE, value_ptr(camera->getRotation() * camera->getTranslation()));
    glUniformMatrix4fv(filling.getLocation("projection"), 1, GL_FALSE, value_ptr(camera->getPerspective()));

    for (unsigned int t = 0; t < models.size(); t ++) {
        meshStore.getMesh(MeshType(t))->bindIndexes();
        meshStore.getMesh(MeshType(t))->draw(models.size(t));
    }

    filling.idle();
}

void Renderer::shadowPass(Aggregator<Model> &models)
{
    shadowVolume.use();

    glUniformMatrix4fv(shadowVolume.getLocation("view"), 1, GL_FALSE, value_ptr(camera->getRotation() * camera->getTranslation()));
    glUniformMatrix4fv(shadowVolume.getLocation("projection"), 1, GL_FALSE, value_ptr(camera->getPerspective()));

    for (unsigned int t = 0; t < models.size(); t ++) {
        for (unsigned int i = 0; i < models.size(t); i++) {
            const Model &model = models.get(t)->at(i);
            vec4 d = directionalLight.direction * model.getRotation();

            glUniformMatrix4fv(shadowVolume.getLocation("model"), 1, GL_FALSE, &model.getProduct()[0][0]);
            glUniform4f(shadowVolume.getLocation("light"), d.x, d.y, d.z, d.w);

            meshStore.getMesh(MeshType(t))->updateShadowVolume(d);
            meshStore.getMesh(MeshType(t))->bindSilhouette();
            meshStore.getMesh(MeshType(t))->drawShadowVolume();
        }
    }

    shadowVolume.idle();
}

void Renderer::geometryPass(Aggregator<Model> &models)
{
    geometryBuffer.use();

    glUniform1i(geometryBuffer.getLocation("texture_diffuse1"), 0);
    glUniform1i(geometryBuffer.getLocation("texture_specular1"), 1);
    glUniformMatrix4fv(geometryBuffer.getLocation("view"), 1, GL_FALSE, value_ptr(camera->getRotation() * camera->getTranslation()));
    glUniformMatrix4fv(geometryBuffer.getLocation("projection"), 1, GL_FALSE, value_ptr(camera->getPerspective()));

    for (unsigned int t = 0; t < models.size(); t ++) {
        meshStore.getMesh(MeshType(t))->bindTexture();
        meshStore.getMesh(MeshType(t))->bindIndexes();
        meshStore.getMesh(MeshType(t))->draw(models.size(t));
    }

    geometryBuffer.idle();
}

void Renderer::lightingPass()
{
    deferredShading.use();

    glUniform1i(deferredShading.getLocation("gPosition"), 0);
    glUniform1i(deferredShading.getLocation("gNormal"), 1);
    glUniform1i(deferredShading.getLocation("gAlbedoSpec"), 2);
    glUniform3fv(deferredShading.getLocation("light.color"), 1, value_ptr(directionalLight.color));
    glUniform3fv(deferredShading.getLocation("light.direction"), 1, value_ptr(directionalLight.direction));
    glUniform3fv(deferredShading.getLocation("view_position"), 1, value_ptr(camera->getPosition()));

    gBuffer.bindTextures();

    quad.draw();

    deferredShading.idle();
}
