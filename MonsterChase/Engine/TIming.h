#pragma once
#define DESIRED_FPS		60.0f
#define DESIRED_FRAMETIME_MS	(1000.0f / DESIRED_FPS)
#define MAX_FRAMETIME_MS	(2 * DESIRED_FRAMETIME_MS)

namespace Timing {
	float CalcLastFrameTime_ms();
	double GetCounter();
	double GetFrequency();
	double GetTimeDiff_ms(double startTime, double endTime);
}
