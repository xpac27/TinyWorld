#include "catch.hpp"
#include "../../inc/ecs/EntityManager.hpp"
#include "../../inc/ecs/Id.hpp"

namespace
{
    SCENARIO("EntityManager" "[EntityManager, addEntity]")
    {
        GIVEN("An EntityManager") {
            ECS::EntityManager entityManager;

            WHEN("No entity are added") {
                THEN("addEntity returns 0") {
                    CHECK(entityManager.addEntity() == 0);
                }
            }

            WHEN("2 entities are added") {
                ECS::id e1 = entityManager.addEntity();
                ECS::id e2 = entityManager.addEntity();

                THEN("The entities are valid") {
                    CHECK(e1 == 0);
                    CHECK(e2 == 1);
                }

                THEN("addEntity returns 2") {
                    CHECK(entityManager.addEntity() == 2);
                }
            }
        }
    }

    SCENARIO("EntityManager" "[EntityManager, getTotal]")
    {
        GIVEN("An EntityManager") {
            ECS::EntityManager entityManager;

            WHEN("No entity are added") {
                THEN("getTotal returns 0") {
                    CHECK(entityManager.getTotal() == 0);
                }
            }

            WHEN("3 entities are added") {
                entityManager.addEntity();
                entityManager.addEntity();
                entityManager.addEntity();

                THEN("getTotal returns 3") {
                    CHECK(entityManager.getTotal() == 3);
                }
            }
        }
    }
}
