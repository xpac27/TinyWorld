#include "catch.hpp"
#include "../../../inc/utils/Store.hpp"
#include <iostream>

struct ItemData { int value; };
class Item {
public:
    Item(ItemData data) : value(data.value) {
        (void)value;
    }
    int value = 0;
};

namespace
{
    SCENARIO("A store returns a stored item") {
        GIVEN("a store with 1 item at index 2") {
            Store<Item, ItemData> items;
            items.init(2, { .value = 123});

            WHEN("geting item at index 2") {
                std::unique_ptr<Item>& item = items.get(2);

                THEN("the returned item is correct") {
                    CHECK(item.get()->value == 123);
                }
            }
        }
    }

    SCENARIO("A store returns multiple stored item") {
        GIVEN("a store with 3 items at index 0, 1 and 2") {
            Store<Item, ItemData> items;
            items.init(0, { .value = 111});
            items.init(1, { .value = 222});
            items.init(2, { .value = 333});

            WHEN("geting item at index 0") {
                std::unique_ptr<Item>& item = items.get(0);

                THEN("the returned item is correct") {
                    CHECK(item.get()->value == 111);
                }
            }

            WHEN("geting item at index 1") {
                std::unique_ptr<Item>& item = items.get(1);

                THEN("the returned item is correct") {
                    CHECK(item.get()->value == 222);
                }
            }

            WHEN("geting item at index 2") {
                std::unique_ptr<Item>& item = items.get(2);

                THEN("the returned item is correct") {
                    CHECK(item.get()->value == 333);
                }
            }
        }
    }

    SCENARIO("A store doesn't replaced an already existing value") {
        GIVEN("a store with 1 item at index 0") {
            Store<Item, ItemData> items;
            items.init(0, { .value = 999});

            WHEN("initing item at index 0 again") {
                items.init(0, { .value = 888});

                AND_WHEN("geting item at index 0") {
                    std::unique_ptr<Item>& item = items.get(0);

                    THEN("the returned item is correct") {
                        CHECK(item.get()->value == 999);
                    }
                }
            }
        }
    }

    SCENARIO("A cleared store can have items re-added") {
        GIVEN("a store with 1 item at index 0") {
            Store<Item, ItemData> items;
            items.init(0, { .value = 999});

            WHEN("clearing the store and initing item at index 0 again") {
                items.clear();
                items.init(0, { .value = 888});

                AND_WHEN("geting item at index 0") {
                    std::unique_ptr<Item>& item = items.get(0);

                    THEN("the returned item is correct") {
                        CHECK(item.get()->value == 888);
                    }
                }
            }
        }
    }

}
