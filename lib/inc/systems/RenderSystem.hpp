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
    void render(glm::vec3 eyePosition);
    void depthPass();
    void shadowPass();
    void colorPass(glm::vec3 eyePosition);
    void initializeShader(Program &program, const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

    Program rendering;
    Program shadowing;
    Program filling;
    DirectionalLight light;
    Aggregator<glm::mat4> WVPprojections;
    Aggregator<glm::mat4> Wprojections;
    Aggregator<glm::vec3> rotations;

    // TODO wrap that in a class
    GLint renderingShaderTextureUnit = 0;
    GLint renderingShaderLightColor = 0;
    GLint renderingShaderLightAmbientIntensity = 0;
    GLint renderingShaderLightDiffuseIntensity = 0;
    GLint renderingShaderSpecularIntensity = 0;
    GLint renderingShaderSpecularPower = 0;
    GLint renderingShaderLightDirection = 0;
    GLint renderingShaderEyeWorldPosition = 0;
    GLint shadowingShaderLight = 0;
    GLint shadowingShaderWVP = 0;

    float count = 0.f;

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Movement>* movementComponents;

    // TODO init from outside (systems class?)
    MeshStore* meshStore;
};
