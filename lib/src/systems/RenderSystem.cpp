#include "systems/RenderSystem.hpp"
#include "ecs/ComponentManager.hpp"
#include "ecs/Id.hpp"
#include "utils/Log.hpp"
#include "graphic/Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <math.h>

using namespace std;
using namespace glm;
using namespace Log;
using namespace ECS;

RenderSystem::RenderSystem(
    ComponentManager<Visibility>* vc,
    ComponentManager<Movement>* mc
)
    : System({vc, mc})
    , visibilityComponents(vc)
    , movementComponents(mc)
    , renderer(new Renderer())
{
}

RenderSystem::~RenderSystem()
{
    delete renderer;
}

void RenderSystem::initialize()
{
    renderer->initialize();
}

void RenderSystem::update()
{
    for (unsigned int i = 0; i < getEntities()->size(); i ++) {
        id entity = getEntities()->at(i);

        if (visibilityComponents->hasComponent(entity)) {
            Visibility* visibility = visibilityComponents->getComponent(entity);

            mat4 modelRotation;
            mat4 modelTranslation;
            mat4 modelScale = scale(mat4(1.0f), visibility->scale);

            if (movementComponents->hasComponent(entity)) {
                Movement* movement = movementComponents->getComponent(entity);

                modelTranslation = translate(mat4(1.0f), movement->position);
                modelRotation = orientation(movement->direction, vec3(-1.0f, 0.0f, 0.0f));
                modelRotation = rotate(modelRotation, count, vec3(0.0f, 0.0f, 1.0f));
            }

            modelMatrices.add(visibility->meshType, modelTranslation * modelRotation * modelScale);
            // modelRotations.add(visibility->meshType, rotate(directionalLight.direction, count * -1, vec3(0.f, 0.f, 1.f)));
        }
    }

    count += 0.01;

    renderer->render(modelMatrices, modelRotations);
    modelRotations.clear();
    modelMatrices.clear();
}
