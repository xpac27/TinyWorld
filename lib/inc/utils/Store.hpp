#pragma once
#include <vector>
#include <memory>
#include <utility>
#include <assert.h>

template <typename K, typename C, typename A>
class Store
{

public:

    void insert(K key, A arguments);

    unsigned int getId(K key);

    std::unique_ptr<C>& get(K key);
    std::unique_ptr<C>& getById(unsigned int id);

private:

    int findId(K key);

    std::vector<std::unique_ptr<C>> items;
    std::vector<std::pair<K, unsigned int>> ids;
};

template <typename K, typename C, typename A>
void Store<K, C, A>::insert(K key, A arguments)
{
    if (findId(key) == -1) {
        ids.push_back(std::make_pair(key, items.size()));
        items.emplace_back(std::move(new C(arguments)));
    }
}

template <typename K, typename C, typename A>
int Store<K, C, A>::findId(K key)
{
    for (auto& pair : ids) {
        if (pair.first == key) {
            return static_cast<int>(pair.second);
        }
    }
    return -1;
}


template <typename K, typename C, typename A>
unsigned int Store<K, C, A>::getId(K key)
{
    int id = findId(key);
    if (id == -1) {
        throw std::out_of_range("Item has not been inserted, id cannot be found!");
    } else {
        return static_cast<unsigned int>(id);
    }
}

template <typename K, typename C, typename A>
std::unique_ptr<C>& Store<K, C, A>::get(K key)
{
    int id = findId(key);
    if (id == -1) {
        throw std::out_of_range("Item has not been inserted, item cannot be found!");
    } else {
        return items.at(static_cast<unsigned int>(id));
    }
}

template <typename K, typename C, typename A>
std::unique_ptr<C>& Store<K, C, A>::getById(unsigned int id)
{
    return items.at(id);
}
