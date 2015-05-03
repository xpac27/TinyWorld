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
class RenderSystem : public ECS::System {

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
    void loadShaderFile(GLuint& shader, const char* filename);
    void compileShader(GLuint& shader, GLuint& program);
    void linkProgram(GLuint& program);

    MeshFactory* meshFactory;

    glm::mat4 modelScale;
    glm::mat4 modelRotation;
    glm::mat4 modelTranslation;
    glm::mat4 viewTranslation;
    glm::mat4 viewRotation;
    glm::mat4 projection;
    glm::mat4 MVP;

    GLuint shaderProgram = glCreateProgram();
    GLint shaderMVPLocation = 0;

    GLfloat lightPos[4] {0.f, 0.f, 10.f, 1.f};
    GLfloat lightAmb[4] {.1f, .1f, .1f, 1.f};
    GLfloat lightDif[4] {.8f, .8f, .8f, 1.f};

    ECS::ComponentManager<Visibility>* visibilityComponents;
    ECS::ComponentManager<Movement>* movementComponents;
};
