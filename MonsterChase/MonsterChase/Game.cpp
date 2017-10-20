#include "Game.h"

#include "StringPool.h"
#include "Actor.h"


#include<string>



using namespace Engine;

namespace Game {
	HINSTANCE i_hInstance;
	HINSTANCE i_hPrevInstance;
	LPWSTR i_lpCmdLine;
	int i_nCmdShow;



	bool Game::StartUp(HINSTANCE i_h, HINSTANCE i_hPrev, LPWSTR i_lpCmdL, int i_nCmdS) {
		i_hInstance = i_h;
		i_hPrevInstance = i_hPrev;
		i_lpCmdLine = i_lpCmdL;
		i_nCmdShow = i_nCmdS;
		return true;
	}

	void Game::Run() {
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600); 			
		if (bSuccess) {			
			Engine::CreateActor("data\\first_paddle.lua");
			Engine::CreateActor("data\\second_paddle.lua");
			Engine::CreateActor("data\\ball.lua");
			Engine::CreateActor("data\\wall2.lua");
			Engine::CreateActor("data\\wall1.lua");
			Engine::CreateActor("data\\Dummy.lua");
			//Engine::CreateActor("data\\wall3.lua");
		}
		//GLib::Sprites::Sprite * pGoodGuySprite = CreateSprite("data\\GoodGuy.dds");
	}

	bool Game::ShutDown() {
		return true;
	}

	
}