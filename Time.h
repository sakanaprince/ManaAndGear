#pragma once
#include <chrono>

class Time
{
private:
	bool isInitDone{ false };
	std::chrono::system_clock::time_point _currentTime;
	std::chrono::system_clock::time_point _prevTime;


public:
	void Init();
	void StartFrame();
	double GetDeltaTime();
	void EndFrame();

	double GetNowTime()
	{
		return std::chrono::duration<double>(_currentTime.time_since_epoch()).count();
	}
};

