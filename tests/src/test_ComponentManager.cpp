#include "catch.hpp"
#include "ecs/EntityManager.hpp"
#include "ecs/ComponentManager.hpp"
#include "components/Life.hpp"

namespace
{
    SCENARIO("ComponentManager" "[ComponentManager, createComponent]") {
        GIVEN("A Life ComponentManager") {
            ECS::ComponentManager<Life> lifeComponents;

            WHEN("Creating a component") {
                Life *c = lifeComponents.createComponent();

                THEN("A Life component is returned") {
                    CHECK(c);
                    CHECK(c->amount == 100);
                }
            }
        }
    }

    SCENARIO("ComponentManager" "[ComponentManager, addComponent, delComponent, hasComponent]") {
        GIVEN("A Life ComponentManager") {
            ECS::ComponentManager<Life> lifeComponents;

            GIVEN("An entity") {
                ECS::EntityManager entityManager;
                ECS::id e = entityManager.addEntity();

                THEN("Entity doesn't have a component") {
                    CHECK(lifeComponents.hasComponent(e) == false);
                }

                GIVEN("A Life component") {
                    Life *c = lifeComponents.createComponent();

                    THEN("Call to addComponent is valid") {
                        CHECK_NOTHROW(lifeComponents.addComponent(c, e));
                    }

                    GIVEN("A Life component added to an Entity") {
                        lifeComponents.addComponent(c, e);

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
    }

    SCENARIO("ComponentManager" "[ComponentManager, getComponent]") {
        GIVEN("A Life ComponentManager and an entity with a Life component") {
            ECS::ComponentManager<Life> lifeComponents;
            ECS::EntityManager entityManager;
            ECS::id e = entityManager.addEntity();
            Life *c = lifeComponents.createComponent();
            lifeComponents.addComponent(c, e);

            WHEN("Calling getComponent") {
                Life *cc = lifeComponents.getComponent(e);

                THEN("The entity's Life component is returned") {
                    CHECK(c->amount == 100);
                    CHECK(cc->amount == 100);
                    CHECK(cc == c);
                }

                WHEN("Modifying the component's properties") {
                    c->amount = 56789;

                    THEN("The entity's Life component is modified") {
                        CHECK(cc->amount == c->amount);
                        CHECK(cc->amount == 56789);
                    }
                }
            }
        }
    }
}
