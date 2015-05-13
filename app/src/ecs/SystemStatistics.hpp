#pragma once

namespace ECS {

class SystemStatistics
{

public:

    void print(const char* name);
    void updating();
    void updated();

private:

	float averageUpdateFrequency;

	float getTime();
    float averageUpdateDuration {0};
	float updateTime {0};

};
}
