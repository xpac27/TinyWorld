#include "FPS.hpp"
#include <iostream>
#include <math.h>

using namespace std;

void FPS::tick()
{
    frameCount ++;
    if (isReady()) {
        compute();
        print();
        mClock.restart();
        frameCount = 0.f;
    }
}

void FPS::compute()
{
    result = frameCount * mClock.getElapsedTime().asSeconds();
}

bool FPS::isReady() const
{
    return mClock.getElapsedTime().asSeconds() > 1.f;
}

void FPS::print() const
{
    cout << " " << mName << ": " << round(result) << endl;
}
