#pragma once
#include <graphic/Quad.hpp>
#include <graphic/GBuffer.hpp>
#include <graphic/DirectionalLight.hpp>
#include <graphic/RendererParams.hpp>
#include <glm/vec3.hpp>

template <typename T, typename TT, typename TTT>
class Store;
template <typename T>
class Aggregator;
class Camera;
class Model;
class Program;
class MeshStore;
class Cubemap;
class Program;
struct CubemapParams;
struct ProgramParams;

class Renderer
{

public:

    Renderer(
        MeshStore& meshStore,
        Store<const char*, Program, ProgramParams>& programStore,
        Store<const char*, Cubemap, CubemapParams>& cubemapStore
    );
    ~Renderer();

    void render(Aggregator<Model>& models);
    void setup(RendererParams params);

private:

    void uploadMatrices(Aggregator<Model> &models);
    void depthPass(Aggregator<Model> &models);
    void shadowVolumePass(Aggregator<Model> &models);
    void geometryPass(Aggregator<Model> &models);
    void lightingPass();
    void shadowImprintPass();

    RendererParams params;

    MeshStore& meshStore;

    Store<const char*, Program, ProgramParams>& programStore;
    Store<const char*, Cubemap, CubemapParams>& cubemapStore;

    Quad quad;
    GBuffer gBuffer;
    // This should be passed as arguments to the render method (light store?)
    DirectionalLight directionalLight; // Could be entity component
    Camera *camera; // Could be entity component
};
