#pragma once
#include "ecs/Id.hpp"
#include "ecs/System.hpp"
#include "components/Visibility.hpp"
#include "components/Movement.hpp"
#include "graphic/DirectionalLight.hpp"
#include "utils/Program.hpp"
#include "utils/Aggregator.hpp"
#include "utils/FrameBuffer.hpp"
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

    void setGLStates();
    void unsetGLStates();
    void shadowPass();
    void renderPass(glm::vec3 POVPosition);
    void debugPass();

    Program rendering;
    Program shadowing;
    Program debuging;

    DirectionalLight light;

    FrameBuffer frameBuffer;

    Aggregator<glm::mat4> WVPEyeProjections;
    Aggregator<glm::mat4> WVPLightProjections;
    Aggregator<glm::mat4> Wprojections;

    // TODO wrap that in a class
    GLint renderingTextureUnit = 0;
    GLint renderingLightColor = 0;
    GLint renderingLightAmbientIntensity = 0;
    GLint renderingLightDiffuseIntensity = 0;
    GLint renderingSpecularIntensity = 0;
    GLint renderingSpecularPower = 0;
    GLint renderingLightDirection = 0;
    GLint renderingEyeWorldPosition = 0;
    GLint shadowingTextureUnit = 0;
    GLint debugingTextureUnit = 0;

    float count = 0.f;

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Movement>* movementComponents;

    // TODO init from outside (systems class?)
    MeshStore* meshStore;
};
