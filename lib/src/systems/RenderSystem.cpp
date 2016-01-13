#include "../../inc/systems/RenderSystem.hpp"
#include "../../inc/ecs/ComponentManager.hpp"
#include "../../inc/ecs/Id.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/mat4x4.hpp>
#include <math.h>

#include "../utils/Log.hpp"
#include "../graphic/Renderer.hpp"
#include <graphic/Model.hpp> // TODO use relative path
#include <utils/Aggregator.hpp> // TODO use relative path

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
    , models(new Aggregator<Model>())
    , renderer(new Renderer())
{
}

RenderSystem::~RenderSystem()
{
    delete models;
    delete renderer;
}

void RenderSystem::initialize()
{
    renderer->initialize();
}

void RenderSystem::reload()
{
    renderer->reload();
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

            models->add(visibility->meshType, Model(modelTranslation, modelRotation, modelScale));
        }
    }

    count += 0.01;

    renderer->render(*models);
    models->clear();
}
