#pragma once
#include <iostream>
#include "ecs/Id.hpp"

struct Movement;
struct Life;
struct Visibility;

namespace Log
{

enum Color {
	NONE, BLACK, RED, GREEN, YELLOW,
	BLUE, MAGENTA, CYAN, WHITE
};

enum Mode {
	NORMAL, BRIGHT, DIM, UNDERSCORE, BLINK
};

void nl();
void style(Color foreground, Color background = NONE, Mode mode = NORMAL);
void style(Color foreground, Mode mode);
void dump(ECS::id entity);
void dump(Movement* p);
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

template <typename T, typename... Tail>
void warning(T const& f, Tail const&... tail)
{
	style(YELLOW);
	print("WARNING!! ");
    print(f, tail...);
    std::cout << std::endl;
}

template <typename T, typename... Tail>
void error(T const& f, Tail const&... tail)
{
	style(RED);
	print("ERROR!! ");
    print(f, tail...);
    std::cout << std::endl;
}

template <typename T, typename... Tail>
void success(T const& f, Tail const&... tail)
{
	style(GREEN);
	print("SUCCESS: ");
    print(f, tail...);
    std::cout << std::endl;
}

template <typename T, typename... Tail>
void info(T const& f, Tail const&... tail)
{
	style(CYAN);
	print("INFO: ");
    print(f, tail...);
    std::cout << std::endl;
}
}
