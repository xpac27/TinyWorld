#pragma once
#include <string>
#include <SFML/System/Clock.hpp>

class FPS
{
public:

    FPS(std::string name)
        : mName(name)
    {}

    void tick();

private:

    void compute();
    void print() const;
    bool isReady() const;

    sf::Clock mClock;
    std::string mName;

    unsigned int frameCount {0};
    float result {0.f};
};
