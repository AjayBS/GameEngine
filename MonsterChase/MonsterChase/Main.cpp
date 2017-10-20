#include <stdio.h> 
#include <stdlib.h> 
#include<conio.h>
#include<Windows.h>
#include"HeapManager.h"
#include "Point2.h"
#include "Macros.h"
#include "GLib.h"

#include "Engine.h"
#include "Game.h"


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	if (Engine::StartUp(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow))
	{
		Game::StartUp(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow);
		/*while (1)
			{*/
				//float dt = Timing::CalcLastFrameTime_ms();
				Game::Run();
				Engine::Run();
				//Game::Run();
			//	Input::Read();
			//}
			Game::ShutDown();
	}
		Engine::ShutDown();



}

