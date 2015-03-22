#include "catch.hpp"
#include "ecs/EntityManager.hpp"

namespace
{
    SCENARIO("EntityManager" "[addEntity]")
    {
        GIVEN("An EntityManager") {
            ECS::EntityManager entityManager;

            WHEN("No entity are added") {
                THEN("addEntity returns 0") {
                    CHECK(entityManager.addEntity() == 0);
                }
            }

            WHEN("1 entities are added") {
                entityManager.addEntity();

                THEN("addEntity returns 1") {
                    CHECK(entityManager.addEntity() == 1);
                }
            }
        }
    }

    SCENARIO("EntityManager" "[getTotal]")
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
