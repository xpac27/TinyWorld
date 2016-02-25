#pragma once
#include <graphic/Quad.hpp>
#include <graphic/GBuffer.hpp>
#include <graphic/DirectionalLight.hpp>
#include <glm/vec3.hpp>

template <typename T, typename TT, typename TTT>
class Store;
template <typename T>
class Aggregator;
class Camera;
class Model;
class Program;
class MeshStore;
class ProgramStore;
class Cubemap;
class CubemapParams;

class Renderer
{

public:

    Renderer(
        MeshStore& meshStore,
        ProgramStore& programStore,
        Store<const char*, Cubemap, CubemapParams>& cubemapStore
    );
    ~Renderer();

    void render(Aggregator<Model>& models);
    void setCubemapId(unsigned int id);

private:

    void uploadMatrices(Aggregator<Model> &models);
    void depthPass(Aggregator<Model> &models);
    void shadowVolumePass(Aggregator<Model> &models);
    void geometryPass(Aggregator<Model> &models);
    void lightingPass();
    void shadowImprintPass();

    int cubemapId = -1;

    MeshStore& meshStore;
    ProgramStore& programStore;

    Store<const char*, Cubemap, CubemapParams>& cubemapStore;

    Quad quad;
    GBuffer gBuffer;
    // This should be passed as arguments to the render method (light store?)
    DirectionalLight directionalLight; // Could be entity component
    Camera *camera; // Could be entity component
};
