#pragma once
#include "ecs/Id.hpp"
#include "ecs/System.hpp"
#include "components/Visibility.hpp"
#include "components/Movement.hpp"
#include "graphic/DirectionalLight.hpp"
#include "utils/Program.hpp"
#include "utils/Aggregator.hpp"
#include <glm/mat4x4.hpp>
#include <GL/glew.h>

class MeshStore;
class Camera;
namespace ECS {
template <typename T> class ComponentManager;
}

class RenderSystem : public ECS::System
{

public:

    RenderSystem(
        ECS::ComponentManager<Visibility>* vc,
        ECS::ComponentManager<Movement>* mc
    );
    ~RenderSystem();

    void initialize() override;
    void update() override;

private:

    void uploadMatrices();
    void render();
    void render2();
    void render3();
    void depthPass();
    void shadowPass();
    void geometryPass();
    void lightingPass();
    void colorPass();
    void initializeShader(Program &program, const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

    Program shadowVolume;
    Program filling;
    Program geometryBuffer;
    Program deferredShading;
    DirectionalLight light;

    Aggregator<glm::vec3> modelRotations;
    Aggregator<glm::mat4> modelMatrices;

    GLuint gBuffer;
    GLuint gPosition;
    GLuint gNormal;
    GLuint gAlbedoSpec;
    GLuint quadVAO = 0;
    GLuint quadVBO;

    float count = 0.f;

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Movement>* movementComponents;

    // TODO init from outside (systems class?)
    MeshStore* meshStore;
    Camera *camera;
};
