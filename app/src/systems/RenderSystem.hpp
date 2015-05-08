#pragma once
#include "ecs/System.hpp"
#include "components/Visibility.hpp"
#include "components/Movement.hpp"
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ECS {
    template <typename T> class ComponentManager;
}
class MeshFactory;
class Program;
struct DirectionalLight;

class RenderSystem : public ECS::System
{

public:

    RenderSystem(
        ECS::ComponentManager<Visibility>* vc,
        ECS::ComponentManager<Movement>* mc
    );

    void initialize();
    void update();

private:

    void setGLStates();
    void unsetGLStates();

    MeshFactory* meshFactory;
    DirectionalLight* light;
    Program* program;

    glm::vec3 eyePosition;
    glm::vec3 eyeRotation;
    glm::mat4 modelScale;
    glm::mat4 modelRotation;
    glm::mat4 modelTranslation;
    glm::mat4 viewTranslation;
    glm::mat4 viewRotation;
    glm::mat4 perspective;
    glm::mat4 Wprojection;
    glm::mat4 WVPprojection;

    GLint shaderW = 0;
    GLint shaderWVP = 0;
    GLint shaderTextureUnit = 0;
    GLint shaderLightColor = 0;
    GLint shaderLightAmbientIntensity = 0;
    GLint shaderLightDiffuseIntensity = 0;
    GLint shaderSpecularIntensity = 0;
    GLint shaderSpecularPower = 0;
    GLint shaderLightDirection = 0;
    GLint shaderEyeWorldPosition = 0;

    float c {0.f};

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Movement>* movementComponents;
};
