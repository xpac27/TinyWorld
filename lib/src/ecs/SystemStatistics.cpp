#include "SystemStatistics.hpp"
#include "../utils/Log.hpp"
#include <math.h>

using namespace std;

namespace ecs {

void SystemStatistics::print(const char* name)
{
	printl(" ", name, "  ", round(averageUpdateFrequency), "fps", (averageUpdateDuration * 1000.f), "ms");
}

void SystemStatistics::updating()
{
	averageUpdateFrequency *= 9;
   	averageUpdateFrequency += 1.f / (getTime() - updateTime);
	averageUpdateFrequency /= 10;
	updateTime = getTime();
}

void SystemStatistics::updated()
{
	averageUpdateDuration *= 9.f;
	averageUpdateDuration += getTime() - updateTime;
	averageUpdateDuration /= 10.f;
}

float SystemStatistics::getTime()
{
    return 0.f;
    // return float(glfwGetTime());
}
}
