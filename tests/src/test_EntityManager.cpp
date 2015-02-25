#include "catch.hpp"
#include "EntityManager.hpp"
#include "components/Life.hpp"
#include "components/Position.hpp"
#include <iostream>

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

    SCENARIO("EntitiesManager" "[resetEntity]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            WHEN("No entity are added") {
                THEN("Call to delEntity is invalid") {
                    CHECK_THROWS(entityManager.resetEntity(0));
                }
            }

            WHEN("1 entities is added") {
                Index e = entityManager.addEntity();

                THEN("Call to delEntity is valid") {
                    CHECK_NOTHROW(entityManager.resetEntity(e));
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

    SCENARIO("EntitiesManager" "[addComponent]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            THEN("Call to addComponent is invalid") {
                CHECK_THROWS(entityManager.addComponent<Position>(1));
            }

            WHEN("1 entity added") {
                Index e = entityManager.addEntity();

                THEN("Adding a Life component is valid") {
                    CHECK_NOTHROW(entityManager.addComponent<Life>(e));
                }

                WHEN("Life component added to entity") {
                    entityManager.addComponent<Life>(e);

                    THEN("Adding a Life component again is invalid") {
                        CHECK_THROWS(entityManager.addComponent<Life>(e));
                    }
                    THEN("Adding a Position component is valid") {
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
                Index e = entityManager.addEntity();

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

    SCENARIO("EntitiesManager" "[getComponent]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            WHEN("1 entity added") {
                Index e = entityManager.addEntity();

                THEN("Get Life component is invalid") {
                    CHECK_THROWS(entityManager.getComponent<Position>(e));
                }

                WHEN("1 Life component added to entity") {
                    entityManager.addComponent<Life>(e);

                    THEN("Get Life component is valid") {
                        CHECK_NOTHROW(entityManager.getComponent<Life>(e));
                    }
                    THEN("Get Position component is invalid") {
                        CHECK_THROWS(entityManager.getComponent<Position>(e));
                    }
                }
            }
        }
    }

    SCENARIO("EntitiesManager" "[delComponent]") {
        GIVEN("An EntityManager") {
            EntitiesManager entityManager;

            WHEN("1 entity added") {
                Index e = entityManager.addEntity();

                THEN("Call to delComponent is invalid") {
                    CHECK_THROWS(entityManager.delComponent<Position>(e));
                }

                WHEN("1 Life component added to entity") {
                    entityManager.addComponent<Life>(e);

                    THEN("Del Life component is valid") {
                        CHECK_NOTHROW(entityManager.delComponent<Life>(e));
                    }
                    THEN("Del Position component is valid") {
                        CHECK_THROWS(entityManager.delComponent<Position>(e));
                    }
                }
            }
        }
    }
}
