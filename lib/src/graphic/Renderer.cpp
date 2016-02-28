#include "CubemapParams.hpp"
#include "ProgramParams.hpp"
#include "MeshParams.hpp"
#include "Renderer.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "../utils/Store.hpp"
#include "../utils/log.hpp"
#include "../utils/Aggregator.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace std;
using namespace glm;

Renderer::Renderer(
        Store<const char*, Mesh, MeshParams>& _meshStore,
        Store<const char*, Program, ProgramParams>& _programStore,
        Store<const char*, Cubemap, CubemapParams>& _cubemapStore
)
    : meshStore(_meshStore)
    , programStore(_programStore)
    , cubemapStore(_cubemapStore)
    , camera(new Camera(0.f, -5.f, 5.f, float(M_PI) * -0.25f, 0.f, 0.f))
{
    // TODO make this date driven
    directionalLight.color = vec3(1.0, 0.9, 0.8);
    directionalLight.ambiant = vec3(0.44, 0.24, 0.04);
    directionalLight.direction = normalize(vec4(1.f, 1.f, -0.3f, 0.f));
}

Renderer::~Renderer()
{
    delete camera;
}

void Renderer::setup(RendererParams _params)
{
    params = _params;
}

void Renderer::render(Aggregator<Model> &models)
{
    // Setup
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

    uploadMatrices(models);

    // Off screen rendering
    gBuffer.bind();

    // Render depth
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);
    depthPass(models);

    // Render shadows
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFFL);
    glStencilOpSeparate(GL_FRONT,GL_KEEP,GL_KEEP,GL_INCR_WRAP);
    glStencilOpSeparate(GL_BACK ,GL_KEEP,GL_KEEP,GL_DECR_WRAP);
    glDepthFunc(GL_LESS);
    shadowVolumePass(models);

    // Imprint shadows
    glEnable(GL_CULL_FACE);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glStencilFunc(GL_EQUAL, 0, 0xFFFFFFFFL);
    glDepthFunc(GL_LEQUAL);
    glColorMask(GL_ONE, GL_ONE, GL_ONE, GL_ONE);
    glClear(GL_COLOR_BUFFER_BIT);
    shadowImprintPass();

    // Render scene
    glDisable(GL_STENCIL_TEST);
    geometryPass(models);

    // On screen rendering
    gBuffer.idle();

    // Render lighting
    glDepthMask(GL_TRUE);
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
        meshStore.getById(t)->updateMatrices(totalModels, matrices.data());
    }
}

void Renderer::depthPass(Aggregator<Model> &models)
{
    unique_ptr<Program>& program = programStore.getById(params.fillingProgramId);
    program->use();

    glUniformMatrix4fv(program->getLocation("view"), 1, GL_FALSE, value_ptr(camera->getRotation() * camera->getTranslation()));
    glUniformMatrix4fv(program->getLocation("projection"), 1, GL_FALSE, value_ptr(camera->getPerspective()));

    for (unsigned int t = 0; t < models.size(); t ++) {
        meshStore.getById(t)->draw(models.size(t));
    }

    program->idle();
}

void Renderer::shadowVolumePass(Aggregator<Model> &models)
{
    unique_ptr<Program>& program = programStore.getById(params.shadowVolumeProgramId);
    program->use();

    glUniformMatrix4fv(program->getLocation("view"), 1, GL_FALSE, value_ptr(camera->getRotation() * camera->getTranslation()));
    glUniformMatrix4fv(program->getLocation("projection"), 1, GL_FALSE, value_ptr(camera->getPerspective()));
    glUniform4fv(program->getLocation("direct_light_direction"), 1, value_ptr(directionalLight.direction));

    for (unsigned int t = 0; t < models.size(); t ++) {
        meshStore.getById(t)->drawAdjacency(models.size(t));
    }

    program->idle();
}

void Renderer::shadowImprintPass()
{
    unique_ptr<Program>& program = programStore.getById(params.shadowImprintProgramId);
    program->use();

    quad.draw();

    program->idle();
}

void Renderer::geometryPass(Aggregator<Model> &models)
{
    unique_ptr<Program>& program = programStore.getById(params.geometryBufferProgramId);
    program->use();

    glUniform1i(program->getLocation("texture_diffuse"), 0);
    glUniform1i(program->getLocation("texture_metallic"), 1);
    glUniform1i(program->getLocation("texture_rough"), 2);
    glUniform1i(program->getLocation("texture_normal"), 3);
    glUniformMatrix4fv(program->getLocation("view"), 1, GL_FALSE, value_ptr(camera->getRotation() * camera->getTranslation()));
    glUniformMatrix4fv(program->getLocation("projection"), 1, GL_FALSE, value_ptr(camera->getPerspective()));

    for (unsigned int t = 0; t < models.size(); t ++) {
        meshStore.getById(t)->bindTexture(GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3);
        meshStore.getById(t)->draw(models.size(t));
    }

    program->idle();
}

void Renderer::lightingPass()
{
    unique_ptr<Program>& program = programStore.getById(params.deferredShadingProgramId);
    program->use();

    glUniform1i(program->getLocation("g_position"), 0);
    glUniform1i(program->getLocation("g_normal"), 1);
    glUniform1i(program->getLocation("g_diffuse"), 2);
    glUniform1i(program->getLocation("g_mr"), 3);
    glUniform1i(program->getLocation("g_shadow"), 4);
    glUniform1i(program->getLocation("environment"), 5);
    glUniform1i(program->getLocation("irradiance_map"), 6);
    glUniform3fv(program->getLocation("ambiant_color"), 1, value_ptr(directionalLight.ambiant));
    glUniform3fv(program->getLocation("direct_light_color"), 1, value_ptr(directionalLight.color));
    glUniform3fv(program->getLocation("direct_light_direction"), 1, value_ptr(directionalLight.direction * -1.f));
    glUniform3fv(program->getLocation("view_position"), 1, value_ptr(camera->getPosition()));
    glUniform1f(program->getLocation("gamma"), 2.2);

    gBuffer.bindTextures(GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4);
    cubemapStore.getById(params.cubemapId)->bind(GL_TEXTURE5);
    cubemapStore.getById(params.cubemapId)->bind(GL_TEXTURE6);

    quad.draw();

    program->idle();
}
