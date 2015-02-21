#pragma once
#include <iostream>
#include "components/Position.hpp"
#include "components/Life.hpp"
#include "components/Visibility.hpp"

namespace Debug
{
    void dump(Position* p);
    void dump(Life* p);
    void dump(Visibility* p);

    template <typename T>
    void print(const T p)
    {
        std::cout << p;
    }

    template <typename T>
    void printl(const T p)
    {
        print(p);
        std::cout << std::endl;
    }

    template<typename T, typename... Tail>
    void print(T const& f, Tail const&... tail)
    {
        std::cout << f << " ";
        print(tail...);
    }

    template<typename T, typename... Tail>
    void printl(T const& f, Tail const&... tail)
    {
        print(f, tail...);
        std::cout << std::endl;
    }
}
