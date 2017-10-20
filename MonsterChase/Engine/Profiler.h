#pragma once
#undef min
#undef max
#include "TIming.h"
#include<stdint.h>
#include<limits>
#include<map>

namespace Profile {
	class Profiler
	{
		
	public:
		Profiler();
		~Profiler();
		std::map<const char *, struct Accumulator *> m_AllAccumulators;
		void RegisterAccumulator(const char * i_pName, struct Accumulator & i_Accumulator);
	
	};

	

	static Profiler *g_Profiler;
	Profile::Profiler& GetProfiler();
	void SetProfiler();


	struct Accumulator
	{
		double		m_Sum;
		uint64_t	m_Count;
		double		m_Min, m_Max;

		Accumulator(const char * i_pName) :
			m_Sum(0.0),
			m_Count(0),
			m_Max(std::numeric_limits<float>::min()),
			m_Min(std::numeric_limits<float>::max())
		{
			/*GetAllAccumulators().insert(std::pair<const char *, struct Accumulator *>(i_pName,*this));*/
		GetProfiler().RegisterAccumulator(i_pName, *this);
		}

		void operator+=(double i_time)
		{
			m_Sum += i_time;
			m_Count++;

			if (i_time > m_Max)
				m_Max = i_time;
			else if (i_time < m_Min)
				m_Min = i_time;
		}

		double average()
		{
			return m_Sum / m_Count;
		}
	};


	class ScopedTimer
	{
		double m_Start;
		Profile::Accumulator *m_pAccumulator;
		const char *	m_pScopeName;

	public:
		ScopedTimer(Profile::Accumulator & i_MyAccumulator) :
			m_Start(Timing::GetCounter()),
			m_pAccumulator(&i_MyAccumulator)
		{}

		~ScopedTimer()
		{
			*m_pAccumulator += Timing::GetTimeDiff_ms(m_Start, Timing::GetCounter());
		}
	};




}

#define CONCAT_HELPER(left, right) left##right
#define CONCAT(left, right) CONCAT_HELPER(left, right)
#if defined(ENABLE_PROFILING)
#define PROFILE_UNSCOPED(name) static Profile::Accumulator CONCAT(MyAccumulator, __LINE__)(name); Profile::ScopedTimer MyTimer(CONCAT(MyAccumulator, __LINE__));
#define PROFILE_SCOPE_BEGIN(name) { static Profile::Accumulator CONCAT(MyAccumulator, __LINE__)(name); 	Profile::ScopedTimer MyTimer(CONCAT(MyAccumulator, __LINE__));
#define PROFILE_SCOPE_END()	}
#else
#define PROFILE_SCOPE_BEGIN(str)	__noop
#define PROFILE_SCOPE_END		__noop
#define PROFILE_UNSCOPED(str)	__noop

#endif // ENABLE_PROFILING