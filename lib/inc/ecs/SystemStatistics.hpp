#pragma once

namespace ecs {

class SystemStatistics
{

public:

    void print(const char* name);
    void updating();
    void updated();

private:

	float getTime();
    float averageUpdateDuration {0.0};
	float updateTime {0.0};
	float averageUpdateFrequency {1.0};
};
}
