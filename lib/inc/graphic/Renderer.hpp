#pragma once
#include <graphic/Quad.hpp>
#include <graphic/GBuffer.hpp>
#include <graphic/DirectionalLight.hpp>
#include <glm/vec3.hpp>

template <typename T>
class Aggregator;
class Camera;
class Model;
class Program;
class MeshStore;
class ProgramStore;
class CubemapStore;

class Renderer
{

public:

    Renderer(MeshStore& meshStore, ProgramStore& programStore, CubemapStore& cubemapStore);
    ~Renderer();

    void render(Aggregator<Model>& models);

private:

    void uploadMatrices(Aggregator<Model> &models);
    void depthPass(Aggregator<Model> &models);
    void shadowVolumePass(Aggregator<Model> &models);
    void geometryPass(Aggregator<Model> &models);
    void lightingPass();
    void shadowImprintPass();

    MeshStore& meshStore;
    ProgramStore& programStore;
    CubemapStore& cubemapStore;

    Quad quad;
    GBuffer gBuffer;
    // This should be passed as arguments to the render method
    DirectionalLight directionalLight; // Could be entity component
    Camera *camera; // Could be entity component
};
