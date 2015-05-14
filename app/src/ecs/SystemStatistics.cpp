#include "SystemStatistics.hpp"
#include "utils/Log.hpp"
#include <math.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace Log;

namespace ECS {

void SystemStatistics::print(const char* name)
{
	printl("--", name, "-", round(averageUpdateFrequency), "-", averageUpdateDuration);
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
	averageUpdateDuration *= 9;
	averageUpdateDuration += getTime() - updateTime;
	averageUpdateDuration /= 10;
}

float SystemStatistics::getTime()
{
    return float(glfwGetTime());
}
}
