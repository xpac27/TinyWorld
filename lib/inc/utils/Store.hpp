#pragma once
#include <vector>
#include <memory>
#include <assert.h>

template <typename C, typename A>
class Store
{

public:

    void init(unsigned int index, A arguments);
    void clear();

    std::unique_ptr<C>& get(unsigned int index);

private:

    void checkCapacity(unsigned int index);

    std::vector<std::unique_ptr<C>> itemLists = {};
};

template <typename C, typename A>
void Store<C, A>::clear()
{
    for (auto& item : itemLists) {
        item.release();
    }
}

template <typename C, typename A>
void Store<C, A>::init(unsigned int index, A arguments)
{
    checkCapacity(index);
    if (!itemLists.at(index)) {
        itemLists.at(index).reset(new C(arguments));
    }
}

template <typename C, typename A>
std::unique_ptr<C>& Store<C, A>::get(unsigned int index)
{
    assert(index < itemLists.size() && itemLists.at(index) && "index out of bounds");
    return itemLists.at(index);
}

template <typename C, typename A>
void Store<C, A>::checkCapacity(unsigned int index)
{
    if (index >= itemLists.size()) {
        itemLists.resize(index + 1);
    }
}
