#include "catch.hpp"
#include "../../../inc/utils/Path.hpp"
#include <iostream>

namespace
{
    SCENARIO("Path can be converted to char") {

        GIVEN("a path") {
            Path tmp("/tmp");

            THEN("it return the correct location") {
                CHECK(tmp.get() == "/tmp");
            }
        }
    }

    SCENARIO("Path can be created relative to each other") {

        GIVEN("a path") {
            Path tmp("/tmp");

            WHEN("geting a relative path from it") {
                Path something(tmp.get("somewhere/else"));

                THEN("the resulting path's location is correct") {
                    CHECK(something.get() == "/tmp/somewhere/else");
                }
            }
        }
    }
}
