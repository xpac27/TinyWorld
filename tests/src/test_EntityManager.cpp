#include "hamlest.hpp"
#include "EntityManager.hpp"
#define CASE( name ) lest_CASE( specification(), name )
using namespace lest::matchers;

extern lest::tests & specification();

namespace
{
    CASE("EntitiesManager" "[getEntityCount]")
    {
        SETUP("An EntityManager")
        {
            EntitiesManager entityManager;

            SECTION("adding 3 entities increase entity count")
            {
                entityManager.addEntity();
                entityManager.addEntity();
                entityManager.addEntity();

                EXPECT_THAT(entityManager.getEntityCount(), equal_to(3));
            }
        }
    }
}
