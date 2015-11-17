#pragma once
#include "utils/Program.hpp"
#include "utils/Aggregator.hpp"
#include "graphic/Model.hpp"
#include "graphic/MeshStore.hpp"
#include "graphic/GBuffer.hpp"
#include "graphic/Quad.hpp"
#include "graphic/DirectionalLight.hpp"
#include <glm/vec3.hpp>

class Camera;

class Renderer
{

public:

    Renderer();
    ~Renderer();

    void initialize();
    void render(Aggregator<Model> &models);

private:

    void uploadMatrices(Aggregator<Model> &models);
    void depthPass(Aggregator<Model> &models);
    void shadowPass(Aggregator<Model> &models);
    void geometryPass(Aggregator<Model> &models);
    void lightingPass();
    void initializeShader(Program &program, const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

    Program shadowVolume;
    Program filling;
    Program geometryBuffer;
    Program deferredShading;

    Quad quad;
    GBuffer gBuffer;
    MeshStore meshStore;
    DirectionalLight directionalLight;

    // TODO init from outside (systems class?)
    Camera *camera;
};
