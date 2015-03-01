#pragma once
#include <vector>
#include <climits>

namespace ECS
{

template <class B>      // CRT Patern Object Register
struct Component {
    static unsigned int typeIndex;
    static std::vector<B>& list;
};
template <class B>
unsigned int Component<B>::typeIndex = UINT_MAX;
template <class B>
std::vector<B>& Component<B>::list = *new std::vector<B>();

}
