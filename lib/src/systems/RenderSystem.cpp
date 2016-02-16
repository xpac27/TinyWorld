#include "../../inc/systems/RenderSystem.hpp"
#include "../../inc/ecs/ComponentManager.hpp"
#include "../../inc/ecs/Id.hpp"
#include "../../inc/graphic/Renderer.hpp"
#include "../../inc/graphic/Model.hpp"
#include "../../inc/utils/Aggregator.hpp"
#include "../utils/log.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/mat4x4.hpp>
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
                modelRotation = rotate(modelRotation, count, vec3(0.0f, 0.0f, 1.0f));
            }

            models.add(visibility->meshType, Model(modelTranslation, modelRotation, modelScale));
        }
    }

    count += 0.01;

    renderer.render(models);
}
