#include "graphic/Renderer.hpp"
#include "graphic/MeshStore.hpp"
#include "graphic/Mesh.hpp"
#include "graphic/Camera.hpp"
#include "utils/Shader.hpp"
#include "utils/Log.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <GL/glew.h>

using namespace std;
using namespace glm;
using namespace Log;

Renderer::Renderer()
    : meshStore(new MeshStore())
    , camera(new Camera(0.f, -3.f, 8.f, float(M_PI) / -5.f, 0.f, 0.f))
{
    // TODO make this date driven
    directionalLight.color = vec3(1.0, 0.9, 0.7);
    directionalLight.direction = normalize(vec3(1.f, 1.f, -1.f));
    directionalLight.ambientIntensity = 0.2f;
    directionalLight.diffuseIntensity = 1.0f;
    directionalLight.intensity = 1.0f;
}

Renderer::~Renderer()
{
    delete meshStore;
    delete camera;
}

void Renderer::initialize()
{
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

    initializeShader(shadowVolume, "app/res/shaders/shadow_volume.vs", "app/res/shaders/shadow_volume.fs");
    initializeShader(filling, "app/res/shaders/filling.vs", "app/res/shaders/filling.fs");
    initializeShader(geometryBuffer, "app/res/shaders/geometry_buffer.vs", "app/res/shaders/geometry_buffer.fs");
    initializeShader(deferredShading, "app/res/shaders/deferred_shading.vs", "app/res/shaders/deferred_shading.fs");

    // TODO GBuffer class
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
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    // - Finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        error("Framebuffer failed for GBuffer!");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // ----

    // TODO have that separatly
    GLfloat quadVertices[] = {
        // Positions        // Texture Coords
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
    };
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<const GLvoid *>(sizeof(GLfloat) * 3));
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

void Renderer::render(Aggregator<glm::mat4> &modelMatrices, Aggregator<glm::vec3> &modelRotations)
{
    uploadMatrices(modelMatrices);

    // Off screen rendering
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    // Render depth
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClear(GL_DEPTH_BUFFER_BIT);

    glDepthFunc(GL_LEQUAL);
    depthPass(modelMatrices);;

    // Render shadows
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFFL);
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_KEEP,GL_INCR_WRAP);
    glStencilOpSeparate(GL_BACK ,GL_KEEP,GL_KEEP,GL_DECR_WRAP);
    glDepthFunc(GL_LESS);

    shadowPass(modelMatrices, modelRotations);

    // Render scene
    glEnable(GL_CULL_FACE);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glStencilFunc(GL_EQUAL, 0, 0xFFFFFFFFL);
    glDepthFunc(GL_LEQUAL);
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT);

    geometryPass(modelMatrices);

    // On screen rendering
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

void Renderer::uploadMatrices(Aggregator<glm::mat4> &modelMatrices)
{
    for (unsigned int t = 0; t < modelMatrices.size(); t ++) {
        meshStore->getMesh(MeshType(t))->updateMatrices(modelMatrices.size(t), modelMatrices.get(t)->data());
    }
}

void Renderer::depthPass(Aggregator<glm::mat4> &modelMatrices)
{
    filling.use();

    glUniformMatrix4fv(filling.getLocation("view"), 1, GL_FALSE, value_ptr(camera->getTranslation() * camera->getRotation()));
    glUniformMatrix4fv(filling.getLocation("projection"), 1, GL_FALSE, value_ptr(camera->getPerspective()));

    for (unsigned int t = 0; t < modelMatrices.size(); t ++) {
        meshStore->getMesh(MeshType(t))->bindIndexes();
        meshStore->getMesh(MeshType(t))->draw(modelMatrices.size(t));
    }

    filling.idle();
}

void Renderer::shadowPass(Aggregator<glm::mat4> &modelMatrices, Aggregator<glm::vec3> &modelRotations)
{
    shadowVolume.use();

    glUniformMatrix4fv(shadowVolume.getLocation("view"), 1, GL_FALSE, value_ptr(camera->getTranslation() * camera->getRotation()));
    glUniformMatrix4fv(shadowVolume.getLocation("projection"), 1, GL_FALSE, value_ptr(camera->getPerspective()));

    for (unsigned int t = 0; t < modelRotations.size(); t ++) {
        for (unsigned int i = 0; i < modelRotations.size(t); i++) {
            glUniformMatrix4fv(shadowVolume.getLocation("model"), 1, GL_FALSE, &modelMatrices.get(t)->at(i)[0][0]);
            glUniform4f(shadowVolume.getLocation("light"), modelRotations.get(t)->at(i).x, modelRotations.get(t)->at(i).y, modelRotations.get(t)->at(i).z, 0.f);

            meshStore->getMesh(MeshType(t))->updateShadowVolume(modelRotations.get(t)->at(i));
            meshStore->getMesh(MeshType(t))->bindSilhouette();
            meshStore->getMesh(MeshType(t))->drawShadowVolume();
        }
    }

    shadowVolume.idle();
}

void Renderer::geometryPass(Aggregator<glm::mat4> &modelMatrices)
{
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
}

void Renderer::lightingPass()
{
    deferredShading.use();

    glUniform1i(deferredShading.getLocation("gPosition"), 0);
    glUniform1i(deferredShading.getLocation("gNormal"), 1);
    glUniform1i(deferredShading.getLocation("gAlbedoSpec"), 2);
    glUniform3f(deferredShading.getLocation("Light.color"), directionalLight.color.x, directionalLight.color.y, directionalLight.color.z);
    glUniform3f(deferredShading.getLocation("Light.direction"), directionalLight.direction.x, directionalLight.direction.y, directionalLight.direction.z);
    glUniform1f(deferredShading.getLocation("Light.intensity"), directionalLight.intensity);

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
