#include "TIming.h"
#include<Windows.h>
//#define CONSTANT_FRAMETIME

double	g_LastFrameStartTick = 0;
float Timing::CalcLastFrameTime_ms() {
	

		float	g_LastFrameTime_ms;

		// Grab the CPU tick counter
		double currentTick = GetCounter();

		if (g_LastFrameStartTick) {
			// How many ticks have elapsed since we last did this
			double elapsedTicks = (currentTick - g_LastFrameStartTick);

			// Calculate the frame time - converting ticks to ms.
			g_LastFrameTime_ms = static_cast<float>(elapsedTicks / (GetFrequency()/100000));
		}
		else {
			g_LastFrameTime_ms = 13.3f; // Assume a 60Hz frame for first call.
		}
		// Note start of this frame
		g_LastFrameStartTick = currentTick;

		#if defined( CONSTANT_FRAMETIME )
		return DESIRED_FRAMETIME_MS;
		#elif defined( CLAMP_FRAMETIME )
		if (LastFrameTime_ms > MAX_FRAMETIME_MS)
			return MAX_FRAMETIME_MS;
		else
			return g_LastFrameTime_ms;
		#else
		return g_LastFrameTime_ms;
		#endif


}

double Timing::GetTimeDiff_ms(double startTime, double endTime) {
	return endTime - startTime;
}

double Timing::GetCounter() {
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	return static_cast<double>(counter.QuadPart);
}

double Timing::GetFrequency() {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	return static_cast<double>(frequency.QuadPart);
}