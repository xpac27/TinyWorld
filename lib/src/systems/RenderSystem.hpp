#pragma once
#include "ecs/Id.hpp"
#include "ecs/System.hpp"
#include "components/Visibility.hpp"
#include "components/Movement.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace ECS {
    template <typename T> class ComponentManager;
}
class MeshStore;
class Program;
struct DirectionalLight;
template <typename T> class Aggregator;

class RenderSystem : public ECS::System
{

public:

    RenderSystem(
        ECS::ComponentManager<Visibility>* vc,
        ECS::ComponentManager<Movement>* mc
    );

    void initialize() override;
    void update() override;

private:

    void setGLStates();
    void unsetGLStates();

    MeshStore* meshStore;
    DirectionalLight* light;
    Program* program;
    Aggregator<glm::mat4>* WVPprojections;
    Aggregator<glm::mat4>* Wprojections;

    // TODO wrap that in a class
    GLint shaderTextureUnit = 0;
    GLint shaderLightColor = 0;
    GLint shaderLightAmbientIntensity = 0;
    GLint shaderLightDiffuseIntensity = 0;
    GLint shaderSpecularIntensity = 0;
    GLint shaderSpecularPower = 0;
    GLint shaderLightDirection = 0;
    GLint shaderEyeWorldPosition = 0;

    float count = 0.f;

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Movement>* movementComponents;
};