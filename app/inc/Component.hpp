#pragma once
#include <vector>
#include <climits>

// CRT Patern Object Register
template <class B>
struct Component {
    static unsigned int typeIndex;
    static std::vector<B>& list;
};
template <class B>
unsigned int Component<B>::typeIndex = UINT_MAX;
template <class B>
std::vector<B>& Component<B>::list = *new std::vector<B>();

// TODO find a better place for that (namespace?)
static unsigned int componentTypeCount = 0;
