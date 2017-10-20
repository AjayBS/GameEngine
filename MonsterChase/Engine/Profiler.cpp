#include "Profiler.h"

Profile::Profiler::Profiler()
{
}

Profile::Profiler::~Profiler()
{
}



void Profile::Profiler::RegisterAccumulator(const char * i_pName, struct Accumulator & i_Accumulator)
{	
	m_AllAccumulators.insert(std::pair<const char *, struct Accumulator *>(i_pName, &i_Accumulator));
}


Profile::Profiler & Profile::GetProfiler()
{
	return *g_Profiler;
}

void Profile::SetProfiler()
{
	g_Profiler = new Profiler();
}
