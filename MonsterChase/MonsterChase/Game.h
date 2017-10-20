#pragma once

#include <stdio.h> 
#include <stdlib.h> 
#include<conio.h>
#include<Windows.h>
#include"HeapManager.h"
#include<Windows.h>

#include "Engine.h"
#include <vector>

namespace Game
{
	void Run();
	bool StartUp(HINSTANCE i_h, HINSTANCE i_hPrev, LPWSTR i_lpCmdL, int i_nCmdS);
	bool ShutDown();
}