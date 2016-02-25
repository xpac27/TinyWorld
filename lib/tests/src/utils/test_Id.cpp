#include "catch.hpp"
#include "../../inc/utils/Id.hpp"

namespace
{
    SCENARIO("Ids can be casted to int") {

        GIVEN("an id") {
            Id id("first");

            WHEN("casting it to string") {
                unsigned int result = id;

                THEN("it returns 0") {
                    CHECK(result == 0);
                }
            }
        }

        GIVEN("two different ids") {
            Id id1("first");
            Id id2("second");

            WHEN("casting them to string") {
                unsigned int result1 = id1;
                unsigned int result2 = id2;

                THEN("it return 0 and 1") {
                    CHECK(result1 == 0);
                    CHECK(result2 == 1);
                }
            }
        }

        GIVEN("two identical ids") {
            Id id1("first");
            Id id2("first");

            WHEN("casting them to string") {
                unsigned int result1 = id1;
                unsigned int result2 = id2;

                THEN("it return 0 and 0") {
                    CHECK(result1 == 0);
                    CHECK(result2 == 0);
                }
            }
        }

        GIVEN("two identical ids and one different") {
            Id id1("first");
            Id id2("second");
            Id id3("first");

            WHEN("casting them to string") {
                unsigned int result1 = id1;
                unsigned int result2 = id2;
                unsigned int result3 = id3;

                THEN("it return 0 and 0") {
                    CHECK(result1 == 0);
                    CHECK(result2 == 1);
                    CHECK(result3 == 0);
                }
            }
        }
    }
}
