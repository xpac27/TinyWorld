#include "catch.hpp"
#include "../../inc/ecs/System.hpp"
#include "../../inc/ecs/ComponentManager.hpp"
#include "../../inc/ecs/EntityManager.hpp"
#include "../../inc/ecs/Id.hpp"
#include "../../inc/components/Life.hpp"

namespace
{
    SCENARIO("System" "[getEntities]") {
        GIVEN("An EntityManager and a ComponentManager") {
            ECS::EntityManager entities {};
            ECS::ComponentManager<Life> lifeComponents {};

            WHEN("Creating a System 2 entities and 2 components") {
                ECS::System system({&lifeComponents});
                ECS::id e1 = entities.addEntity();
                ECS::id e2 = entities.addEntity();

                THEN("The system has no entities") {
                    CHECK(system.getEntities()->size() == 0);
                }

                WHEN("Doing nothing") {
                    THEN("The system has no entities") {
                        CHECK(system.getEntities()->size() == 0);
                    }
                }

                WHEN("Adding 2 components") {
                    lifeComponents.addComponent(e1);
                    lifeComponents.addComponent(e2);

                    THEN("The system has 2 entities") {
                        CHECK(system.getEntities()->size() == 2);
                        CHECK(system.getEntities()->at(0) == e1);
                        CHECK(system.getEntities()->at(1) == e2);
                    }

                    WHEN("Removing 1 components") {
                        lifeComponents.delComponent(e1);

                        THEN("The system has 1 entities") {
                            CHECK(system.getEntities()->size() == 1);
                            CHECK(system.getEntities()->at(0) == e2);
                        }
                    }
                }
            }
        }
    }
}
