#pragma once
#include "../utils/Cubemap.hpp"
#include "MeshStore.hpp"
#include "ProgramStore.hpp"
#include "DirectionalLight.hpp"
#include <glm/vec3.hpp>

template <typename T>
class Aggregator;
class Camera;
class Quad;
class GBuffer;
class Model;
class Program;

class Renderer
{

public:

    Renderer();
    ~Renderer();

    void render(Aggregator<Model>& models);
    void reload();

private:

    void uploadMatrices(Aggregator<Model> &models);
    void depthPass(Aggregator<Model> &models);
    void shadowVolumePass(Aggregator<Model> &models);
    void geometryPass(Aggregator<Model> &models);
    void lightingPass();
    void shadowImprintPass();

    Quad* quad;
    GBuffer* gBuffer;

    // TODO init from outside
    Cubemap environment;
    Cubemap irradianceMap;
    MeshStore meshStore;
    ProgramStore programStore;

    // This should be passed as arguments to the render method
    DirectionalLight directionalLight; // Could be entity component
    Camera *camera; // Could be entity component
};
