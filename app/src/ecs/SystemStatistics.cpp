#include "SystemStatistics.hpp"
#include "utils/Log.hpp"
#include <math.h>

using namespace std;
using namespace std::chrono;
using namespace Log;

namespace ECS {

void SystemStatistics::print(const char* name)
{
	printl("--", name, "-", round(averageUpdateFrequency), "-", averageUpdateDuration.count());
}

void SystemStatistics::updating()
{
	averageUpdateFrequency *= 9;
   	averageUpdateFrequency += 1000.f / float((getTime() - updateTime).count());
	averageUpdateFrequency /= 10;
	updateTime = getTime();
}

void SystemStatistics::updated()
{
	averageUpdateDuration *= 9;
	averageUpdateDuration += getTime() - updateTime;
	averageUpdateDuration /= 10;
}

milliseconds SystemStatistics::getTime()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}
}
