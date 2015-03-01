#pragma once
#include <vector>
#include <climits>

#include "ecs/ComponentGUI.hpp"

namespace ECS
{

template <class B>      // CRT Patern Object Register
struct Component {
    static ComponentGUI id;
    static std::vector<B>& list;
};

template <class T>
unsigned int getComponentId();
template <class T>
unsigned int getComponentMask();

}

template <class B>
ComponentGUI ECS::Component<B>::id = ComponentGUI();
template <class B>
std::vector<B>& ECS::Component<B>::list = *new std::vector<B>();

template <class T>
unsigned int ECS::getComponentId()
{
    return ECS::Component<T>::id.get();
}

template <class T>
unsigned int ECS::getComponentMask()
{
    return 1 << getComponentId<T>();
}
