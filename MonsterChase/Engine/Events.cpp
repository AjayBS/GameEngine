#include "Events.h"

#include "Debug.h"
#include <Windows.h>

namespace Engine
{

	ManualResetEvent::ManualResetEvent(const char * i_pName, bool i_bInitiallySignaled)
	{
		m_Handle = CreateEventA(NULL, TRUE, i_bInitiallySignaled, i_pName);
		assert(m_Handle != INVALID_HANDLE_VALUE);
	}

	ManualResetEvent::~ManualResetEvent()
	{
		CloseHandle(m_Handle);
	}

	void ManualResetEvent::Reset(void)
	{
		ResetEvent(m_Handle);
	}

	bool ManualResetEvent::Wait(wait_t i_WaitMilliseconds)
	{
		DWORD result = WaitForSingleObject(m_Handle, i_WaitMilliseconds);
		assert(((i_WaitMilliseconds == WaitInfinite) && (result == WAIT_OBJECT_0)) || (result == WAIT_TIMEOUT));

		return result == WAIT_OBJECT_0;
	}

	void ManualResetEvent::Signal(void)
	{
		BOOL result = SetEvent(m_Handle);
		assert(result == TRUE);
	}

	AutoResetEvent::AutoResetEvent(const char * i_pName, bool i_bInitiallySignaled)
	{
		m_Handle = CreateEventA(NULL, FALSE, i_bInitiallySignaled, i_pName);
		assert(m_Handle != INVALID_HANDLE_VALUE);
	}

	AutoResetEvent::~AutoResetEvent()
	{
		CloseHandle(m_Handle);
	}

	bool AutoResetEvent::Wait(wait_t i_WaitMilliseconds)
	{
		DWORD result = WaitForSingleObject(m_Handle, i_WaitMilliseconds);
		assert(((i_WaitMilliseconds == WaitInfinite) && (result == WAIT_OBJECT_0)) || (result == WAIT_TIMEOUT));

		return result == WAIT_OBJECT_0;
	}

	void AutoResetEvent::Signal(void)
	{
		BOOL result = SetEvent(m_Handle);
		assert(result == TRUE);
	}


} // namespace Azra