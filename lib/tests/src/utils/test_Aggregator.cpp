#include "catch.hpp"
#include "../../src/utils/Aggregator.hpp"

namespace
{
    SCENARIO("Aggregator") {
        GIVEN("An Aggregator") {
            Aggregator<const char*> aggregator;

            WHEN("Adding an item 'a' in index 0") {
                aggregator.add(0, "a");

                THEN("Index 0 contains 1 item") {
                    CHECK(aggregator.size(0) == 1);
                }

                THEN("Index 0's contains 'a'") {
                    CHECK(aggregator.get(0)->at(0) == "a");
                }
            }
        }

        GIVEN("An Aggregator with 1 item at index 0 and 2 items at index 1") {
            Aggregator<const char*> aggregator;
            aggregator.add(0, "a1");
            aggregator.add(1, "b1");
            aggregator.add(1, "b2");

            WHEN("Clearing index 0") {
                aggregator.clear(0);

                THEN("Index 0 contains 0 items") {
                    CHECK(aggregator.size(0) == 0);
                }
            }

            WHEN("Clearing index 1") {
                aggregator.clear(1);

                THEN("Index 1 contains 0 items") {
                    CHECK(aggregator.size(1) == 0);
                }
            }
        }

        GIVEN("An Aggregator with 1 item at index 0 and 2 items at index 1") {
            Aggregator<const char*> aggregator;
            aggregator.add(0, "a1");
            aggregator.add(1, "b1");
            aggregator.add(1, "b2");

            WHEN("Clearing") {
                aggregator.clear();

                THEN("Index 0 contains 0 items") {
                    CHECK(aggregator.size(0) == 0);
                }

                THEN("Index 1 contains 0 items") {
                    CHECK(aggregator.size(1) == 0);
                }
            }
        }

        GIVEN("An Aggregator with 1 item at index 0 and 2 items at index 1") {
            Aggregator<const char*> aggregator;
            aggregator.add(0, "a1");
            aggregator.add(1, "b1");
            aggregator.add(1, "b2");

            WHEN("Adding an item 'a2' in index 0") {
                aggregator.add(0, "a2");

                THEN("Index 0 contains 2 item") {
                    CHECK(aggregator.size(0) == 2);
                }

                THEN("Index 0's contains 'a1' and 'a2'") {
                    CHECK(aggregator.get(0)->at(0) == "a1");
                    CHECK(aggregator.get(0)->at(1) == "a2");
                }
            }

            WHEN("Adding 2 items 'b3' and 'b4' in index 1") {
                aggregator.add(1, "b3");
                aggregator.add(1, "b4");

                THEN("Index 1 contains 4 item") {
                    CHECK(aggregator.size(1) == 4);
                }

                THEN("Index 1's contains 'b1', 'b2', 'b3' and 'b4'") {
                    CHECK(aggregator.get(1)->at(0) == "b1");
                    CHECK(aggregator.get(1)->at(1) == "b2");
                    CHECK(aggregator.get(1)->at(2) == "b3");
                    CHECK(aggregator.get(1)->at(3) == "b4");
                }
            }

            WHEN("Adding an item 'c1' in index 3") {
                aggregator.add(3, "c1");

                THEN("Index 3 contains 1 item") {
                    CHECK(aggregator.size(3) == 1);
                }

                THEN("Index 3's contains 'c1'") {
                    CHECK(aggregator.get(3)->at(0) == "c1");
                }
            }
        }
    }
}
