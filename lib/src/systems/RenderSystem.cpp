#include "RenderSystem.hpp"
#include "../ecs/ComponentManager.hpp"
#include "../ecs/Id.hpp"
#include "../graphic/Renderer.hpp"
#include "../utils/Aggregator.hpp"
#include "../graphic/Model.hpp"
#include "../utils/Log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/glm.hpp>
#include <math.h>

using namespace std;
using namespace glm;
using namespace ecs;

RenderSystem::RenderSystem(
    ComponentManager<Visibility>* vc,
    ComponentManager<Movement>* mc
)
    : System({vc, mc})
    , visibilityComponents(vc)
    , movementComponents(mc)
{
}

void RenderSystem::update(Renderer& renderer)
{
    Aggregator<Model> models;

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
                modelRotation = rotate(modelRotation, movement->spin, vec3(0.0f, 0.0f, 1.0f));
            }

            models.add(visibility->meshId, Model(modelTranslation, modelRotation, modelScale));
        }
    }

    renderer.render(models);
}
