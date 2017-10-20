#pragma once
#include"HeapManager.h"
#include "ListObjects.h"
#include "../Externals/lua/lua.hpp"
#include"jobsystem.h"
#include"IJob.h"
#include "Messaging.h"
#include "Profiler.h"


namespace Engine 
{	
	bool StartUp(HINSTANCE i_h, HINSTANCE i_hPrev, LPWSTR i_lpCmdL, int i_nCmdS);
	bool ShutDown();
	void Run();

	void CreateActor(const char * i_pLuaFilename);
	uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats);

	ListObjects& GetListOfObjects();
	MessagingSystem::MessageHandler& GetMessageHandler();
	Engine::Mutex& GetMutexForRender();
//	ListObjects * GetListOfObjects();
}

