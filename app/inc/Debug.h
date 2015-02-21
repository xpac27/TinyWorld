#pragma once
#include <iostream>
#include "components/Position.h"
#include "components/Life.h"
#include "components/Visibility.h"

namespace Debug
{
    void print(Position* p);
    void print(Life* p);
    void print(Visibility* p);

    template <typename T>
    void print(const T p)
    {
        std::cout << p << std::endl;
    }

    template<typename T, typename... Tail>
    void print(T const& f, Tail const&... tail)
    {
        std::cout << f << " " << std::endl;
        print(tail...);
    }

    template<typename T, typename... Tail>
    void printl(T const& f, Tail const&... tail)
    {
        print(f, tail...);
        std::cout << std::endl;
    }
}
