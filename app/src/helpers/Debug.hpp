#pragma once
#include <iostream>
#include "ecs/Entity.hpp"

struct Position;
struct Life;
struct Visibility;

namespace Debug
{

void dump(ECS::id entity);
void dump(Position *p);
void dump(Life *p);
void dump(Visibility *p);

void nl();

template <typename T>
void print(const T p)
{
    std::cout << p << "\033[0m";
}

template <typename T>
void printl(const T p)
{
    print(p);
    nl();
}

template <typename T, typename... Tail>
void print(T const& f, Tail const&... tail)
{
    std::cout << f << " ";
    print(tail...);
}

template <typename T, typename... Tail>
void printl(T const& f, Tail const&... tail)
{
    print(f, tail...);
    std::cout << std::endl;
}
}
