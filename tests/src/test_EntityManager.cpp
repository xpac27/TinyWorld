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

    CASE("EntitiesManager" "[addComponent]")
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

                SETUP("register 2 components and add 1 component")
                {
                    entityManager.registerComponent<Position>();
                    entityManager.registerComponent<Life>();
                    entityManager.addComponent<Position>(e);

                    SECTION("addComponent is invalid")
                        EXPECT_NO_THROW(entityManager.addComponent<Life>(e));
                    SECTION("addComponent is valid")
                        EXPECT_THROWS(entityManager.addComponent<Position>(e));
                }
            }
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
