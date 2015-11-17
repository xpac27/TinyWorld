#pragma once
#include "utils/Program.hpp"
#include "utils/Aggregator.hpp"
#include "graphic/DirectionalLight.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class MeshStore;
class Camera;

class Renderer
{

public:

    Renderer();
    ~Renderer();

    void initialize();
    void render(Aggregator<glm::mat4> &modelMatrices, Aggregator<glm::vec3> &modelRotations);

private:

    void uploadMatrices(Aggregator<glm::mat4> &modelMatrices);
    void depthPass(Aggregator<glm::mat4> &modelMatrices);
    void shadowPass(Aggregator<glm::mat4> &modelMatrices, Aggregator<glm::vec3> &modelRotations);
    void geometryPass(Aggregator<glm::mat4> &modelMatrices);
    void lightingPass();
    void initializeShader(Program &program, const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

    // TODO auto detect screen size
    int SCR_WIDTH = 800;
    int SCR_HEIGHT = 600;

    Program shadowVolume;
    Program filling;
    Program geometryBuffer;
    Program deferredShading;

    GLuint gBuffer;
    GLuint gPosition;
    GLuint gNormal;
    GLuint gAlbedoSpec;
    GLuint quadVAO = 0;
    GLuint quadVBO;

    DirectionalLight directionalLight;

    // TODO init from outside (systems class?)
    MeshStore* meshStore;
    Camera *camera;
};
