#include "catch.hpp"
#include "../../src/ecs/System.hpp"
#include "../../src/ecs/ComponentManager.hpp"
#include "../../src/ecs/EntityManager.hpp"
#include "../../src/ecs/Id.hpp"
#include "../../src/components/Life.hpp"

namespace
{
    SCENARIO("System" "[getEntities]") {
        GIVEN("An EntityManager and a ComponentManager") {
            ecs::EntityManager entities {};
            ecs::ComponentManager<Life> lifeComponents {};

            WHEN("Creating a System 2 entities and 2 components") {
                ecs::System system({&lifeComponents});
                ecs::id e1 = entities.addEntity();
                ecs::id e2 = entities.addEntity();

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
