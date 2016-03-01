#include "catch.hpp"
#include "../../../src/utils/Store.hpp"
#include <iostream>
#include <string>

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
    SCENARIO("Inserting items and getting them back") {
        GIVEN("a store with 3 item") {

            Store<std::string, Item, ItemData> items;
            items.insert("first item", {.value = 111});
            items.insert("second item", {.value = 222});
            items.insert("third item", {.value = 333});

            WHEN("geting first item") {
                std::unique_ptr<Item>& item = items.get("first item");

                THEN("the returned item is correct") {
                    CHECK(item.get()->value == 111);
                }
            }

            WHEN("geting second item") {
                std::unique_ptr<Item>& item = items.get("second item");

                THEN("the returned item is correct") {
                    CHECK(item.get()->value == 222);
                }
            }

            WHEN("geting third item") {
                std::unique_ptr<Item>& item = items.get("third item");

                THEN("the returned item is correct") {
                    CHECK(item.get()->value == 333);
                }
            }

            WHEN("geting first item's id") {
                unsigned int id = items.getId("first item");

                THEN("the returned item is correct") {
                    CHECK(id == 0);
                }

                AND_WHEN("getting first item by id") {
                    std::unique_ptr<Item>& item = items.getById(id);

                    THEN("the returned item is correct") {
                        CHECK(item.get()->value == 111);
                    }
                }
            }

            WHEN("geting second item's id") {
                unsigned int id = items.getId("second item");

                THEN("the returned item is correct") {
                    CHECK(id == 1);
                }

                AND_WHEN("getting second item by id") {
                    std::unique_ptr<Item>& item = items.getById(id);

                    THEN("the returned item is correct") {
                        CHECK(item.get()->value == 222);
                    }
                }
            }

            WHEN("geting third item's id") {
                unsigned int id = items.getId("third item");

                THEN("the returned item is correct") {
                    CHECK(id == 2);
                }

                AND_WHEN("getting third item by id") {
                    std::unique_ptr<Item>& item = items.getById(id);

                    THEN("the returned item is correct") {
                        CHECK(item.get()->value == 333);
                    }
                }
            }
        }
    }

    SCENARIO("Inserting the same items again") {
        GIVEN("a store with 3 items") {

            Store<std::string, Item, ItemData> items;
            items.insert("first item", {.value = 111});
            items.insert("second item", {.value = 222});
            items.insert("third item", {.value = 333});

            WHEN("inserting second item once again") {
                items.insert("second item", {.value = 222222});

                AND_WHEN("geting second item") {
                    std::unique_ptr<Item>& item = items.get("second item");

                    THEN("the returned item is correct") {
                        CHECK(item.get()->value == 222);
                    }
                }
            }
        }
    }
}
