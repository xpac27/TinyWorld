#pragma once
#include <chrono>

namespace ECS {

typedef std::chrono::milliseconds milliseconds;

class SystemStatistics
{

public:

    void print(const char* name);
    void updating();
    void updated();

private:

	float averageUpdateFrequency;

	milliseconds getTime();
    milliseconds averageUpdateDuration {0};
	milliseconds updateTime {0};

};
}
