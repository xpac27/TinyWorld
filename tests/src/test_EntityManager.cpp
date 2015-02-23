#include "catch.hpp"
#include "EntityManager.hpp"
#include "components/Life.hpp"
#include "components/Position.hpp"

namespace
{
    SCENARIO("EntitiesManager" "[addEntity]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            WHEN("No entity are added") {
                THEN("addEntity returns 0") {
                    CHECK(entityManager.addEntity() == 0);
                }
            }
            WHEN("3 entities are added") {
                entityManager.addEntity();
                entityManager.addEntity();
                entityManager.addEntity();

                THEN("addEntity returns 3") {
                    CHECK(entityManager.addEntity() == 3);
                }
            }
        }
    }

    SCENARIO("EntitiesManager" "[getEntityCount]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            WHEN("No entity are added") {
                THEN("getEntityCount is 0") {
                    CHECK(entityManager.getEntityCount() == 0);
                }
            }

            WHEN("3 entities are added") {
                entityManager.addEntity();
                entityManager.addEntity();
                entityManager.addEntity();

                THEN("getEntityCount is 3") {
                    CHECK(entityManager.getEntityCount() == 3);
                }
            }
        }
    }

    SCENARIO("EntitiesManager" "[registerComponent-1]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            WHEN("Registering Position component") {
                THEN( "No exeptions are thrown" ) {
                    CHECK_NOTHROW(entityManager.registerComponent<Position>());
                }
            }
        }
    }

    SCENARIO("EntitiesManager" "[registerComponent-2]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            WHEN("Position component is registered") {
                entityManager.registerComponent<Position>();

                THEN("RegisterComponent again is invalid") {
                    CHECK_THROWS(entityManager.registerComponent<Position>());
                }
            }
        }
    }

    SCENARIO("EntitiesManager" "[addComponent]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            WHEN("No component are registered") {
                THEN("Call to addComponent is invalid") {
                    CHECK_THROWS(entityManager.addComponent<Position>(1));
                }

                WHEN("1 entity added") {
                    Entity e = entityManager.addEntity();

                    THEN("Call to addcomponent is invalid") {
                        CHECK_THROWS(entityManager.addComponent<Position>(e));
                    }
                }
            }

            WHEN("Life component registered and 1 entity added") {
                entityManager.registerComponent<Life>();
                Entity e = entityManager.addEntity();

                THEN("Adding a Life component is valid") {
                    CHECK_NOTHROW(entityManager.addComponent<Life>(e));
                }

                WHEN("Position components registered and 1 Life component added to entity") {
                    entityManager.registerComponent<Position>();
                    entityManager.addComponent<Life>(e);

                    THEN("Adding a Life component again is invalid") {
                        CHECK_THROWS(entityManager.addComponent<Life>(e));
                    }
                    THEN("Adding a Position component again is valid") {
                        CHECK_NOTHROW(entityManager.addComponent<Position>(e));
                    }
                }
            }
        }
    }

    SCENARIO("EntitiesManager" "[hasComponent]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            WHEN("No entity are added") {
                THEN("Call to hasComponent is invalid") {
                    CHECK_THROWS(entityManager.hasComponent<Position>(1));
                }
            }

            WHEN("1 entity added") {
                Entity e = entityManager.addEntity();

                THEN("Call to hasComponent is invalid") {
                    CHECK_THROWS(entityManager.hasComponent<Position>(e));
                }

                WHEN("2 components registered") {
                    entityManager.registerComponent<Position>();
                    entityManager.registerComponent<Life>();

                    THEN("The entity doesn't have those components yet") {
                        CHECK(entityManager.hasComponent<Position>(e) == false);
                        CHECK(entityManager.hasComponent<Life>(e) == false);
                    }

                    WHEN("1 Position component added to entity") {
                        entityManager.addComponent<Position>(e);

                        THEN("The entity doesn't have a Life component") {
                            CHECK(entityManager.hasComponent<Life>(e) == false);
                        }
                        THEN("The entity has a Position component") {
                            CHECK(entityManager.hasComponent<Position>(e) == true);
                        }
                    }
                }
            }
        }
    }

    SCENARIO("EntitiesManager" "[getComponent]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            WHEN("No component are registered") {
                THEN("Call to getComponent is invalid") {
                    CHECK_THROWS(entityManager.getComponent<Position>(1));
                }

                WHEN("1 entity added") {
                    Entity e = entityManager.addEntity();

                    THEN("Call to getComponent is invalid") {
                        CHECK_THROWS(entityManager.getComponent<Position>(e));
                    }
                }
            }

            WHEN("Position and Life component registered and 1 entity added") {
                entityManager.registerComponent<Position>();
                entityManager.registerComponent<Life>();
                Entity e = entityManager.addEntity();

                THEN("Get Life component is valid") {
                    CHECK_THROWS(entityManager.getComponent<Position>(e));
                }

                WHEN("1 Life component added to entity") {
                    entityManager.addComponent<Life>(e);

                    THEN("Get Life component is valid") {
                        CHECK_NOTHROW(entityManager.getComponent<Life>(e));
                    }
                    THEN("Get Position component is valid") {
                        CHECK_THROWS(entityManager.getComponent<Position>(e));
                    }
                }
            }
        }
    }
}
