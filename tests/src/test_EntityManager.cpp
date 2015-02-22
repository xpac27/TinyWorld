#include "lest.hpp"
#include "EntityManager.hpp"
#include "components/Position.hpp"
#include "components/Life.hpp"
#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

namespace
{
    CASE("EntitiesManager" "[getEntityCount]")
    {
        SETUP("create an EntityManager")
        {
            EntitiesManager entityManager;

            SECTION("getEntityCount is 0")
                EXPECT(entityManager.getEntityCount() == 0);

            SETUP("add 3 entities")
            {
                entityManager.addEntity();
                entityManager.addEntity();
                entityManager.addEntity();

                SECTION("getEntityCount is 3")
                    EXPECT(entityManager.getEntityCount() == 3);
            }
        }
    }

    CASE("EntitiesManager" "[registerComponent-1]")
    {
        SETUP("create an EntityManager")
        {
            EntitiesManager entityManager;

            SECTION("registerComponent is valid")
                EXPECT_NO_THROW(entityManager.registerComponent<Position>());
        }
    }

    CASE("EntitiesManager" "[registerComponent-2]")
    {
        SETUP("create an EntityManager and register 1 component")
        {
            EntitiesManager entityManager;
            entityManager.registerComponent<Position>();

            SECTION("registerComponent again is invalid")
                EXPECT_THROWS(entityManager.registerComponent<Position>());
        }
    }


    CASE("EntitiesManager" "[addComponent-1]")
    {
        SETUP("create an EntityManager")
        {
            EntitiesManager entityManager;

            SECTION("addComponent is invalid")
                EXPECT_THROWS(entityManager.addComponent<Position>(1));

            SETUP("add 1 entity")
            {
                Entity e = entityManager.addEntity();

                SECTION("addComponent is invalid")
                    EXPECT_THROWS(entityManager.addComponent<Position>(e));

                SETUP("register 1 components")
                {
                    entityManager.registerComponent<Life>();

                    SECTION("addComponent is valid")
                        EXPECT_NO_THROW(entityManager.addComponent<Life>(e));
                }
            }
        }
    }

    CASE("EntitiesManager" "[addComponent-2]")
    {
        SETUP("create an EntitiesManager, add 1 entity, register 2 components, add 1 component")
        {
            EntitiesManager entityManager;
            Entity e = entityManager.addEntity();
            entityManager.registerComponent<Position>();
            entityManager.registerComponent<Life>();
            entityManager.addComponent<Position>(e);

            SECTION("addComponent is valid")
                EXPECT_NO_THROW(entityManager.addComponent<Life>(e));
            SECTION("addComponent again is invalid")
                EXPECT_THROWS(entityManager.addComponent<Position>(e));
        }
    }

    CASE("EntitiesManager" "[hasComponent]")
    {
        SETUP("create an EntityManager")
        {
            EntitiesManager entityManager;

            SECTION("hasComponent is invalid")
                EXPECT_THROWS(entityManager.hasComponent<Position>(1));

            SETUP("add 1 entity")
            {
                Entity e = entityManager.addEntity();

                SECTION("hasComponent is invalid")
                    EXPECT_THROWS(entityManager.hasComponent<Position>(e));

                SETUP("register 2 components")
                {
                    entityManager.registerComponent<Position>();
                    entityManager.registerComponent<Life>();

                    SECTION("hasComponent is false")
                        EXPECT(entityManager.hasComponent<Position>(e) == false);

                    SETUP("add 1 component")
                    {
                        entityManager.addComponent<Position>(e);

                        SECTION("hasComponent is true")
                            EXPECT(entityManager.hasComponent<Position>(e) == true);
                    }
                }
            }
        }
    }
}
