#pragma once
#include <vector>
#include <climits>

namespace ECS
{

typedef unsigned int Index;

template <class B>      // CRT Patern Object Register
struct Component {
    static unsigned int type;
    static std::vector<B>& list;
};

static unsigned int componentTypeCount = 0;

template <class T>
Index getComponentType();

template <class T>
Index getComponentTypeMask();

}

template <class B>
unsigned int ECS::Component<B>::type = UINT_MAX;

template <class B>
std::vector<B>& ECS::Component<B>::list = *new std::vector<B>();

template <class T>
ECS::Index ECS::getComponentType()
{
    if (Component<T>::type == UINT_MAX) {
        Component<T>::type = ++ECS::componentTypeCount - 1;
    }
    return Component<T>::type;
}

template <class T>
unsigned int ECS::getComponentTypeMask()
{
    if (Component<T>::type == UINT_MAX) {
        Component<T>::type = ++ECS::componentTypeCount - 1;
    }
    return 1 << getComponentType<T>();
}
