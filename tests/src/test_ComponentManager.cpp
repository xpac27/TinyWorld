#include "catch.hpp"
#include "ecs/EntityManager.hpp"
#include "ecs/ComponentManager.hpp"
#include "components/Life.hpp"

namespace
{
    SCENARIO("ComponentManager" "[ComponentManager, addComponent, delComponent, hasComponent]") {
        GIVEN("A Life ComponentManager") {
            ECS::ComponentManager<Life> lifeComponents;

            GIVEN("An entity") {
                ECS::EntityManager entityManager;
                ECS::id e = entityManager.addEntity();

                THEN("Entity doesn't have a component") {
                    CHECK(lifeComponents.hasComponent(e) == false);
                }


                GIVEN("A Life component added to an Entity") {
                    lifeComponents.addComponent(e);

                    THEN("Entity have a component") {
                        CHECK(lifeComponents.hasComponent(e) == true);
                    }

                    THEN("Call to delComponent is valid") {
                        CHECK_NOTHROW(lifeComponents.delComponent(e));
                    }

                    GIVEN("A Life component removed from an Entity") {
                        lifeComponents.delComponent(e);

                        THEN("Entity doesn't have a component") {
                            CHECK(lifeComponents.hasComponent(e) == false);
                        }
                    }
                }
            }
        }
    }

    SCENARIO("ComponentManager" "[ComponentManager, getComponent]") {
        GIVEN("A Life ComponentManager and an entity with a Life component") {
            ECS::ComponentManager<Life> lifeComponents;
            ECS::EntityManager entityManager;
            ECS::id e = entityManager.addEntity();
            lifeComponents.addComponent(e);

            WHEN("Calling getComponent") {

                THEN("The entity's Life component is returned") {
                    CHECK(lifeComponents.getComponent(e) != nullptr);
                    CHECK(lifeComponents.getComponent(e)->amount == 100);
                }

                WHEN("Modifying the component's properties") {
                    lifeComponents.getComponent(e)->amount = 56789;

                    THEN("The entity's Life component is modified") {
                        CHECK(lifeComponents.getComponent(e) != nullptr);
                        CHECK(lifeComponents.getComponent(e)->amount == 56789);
                    }
                }
            }
        }
    }
}
