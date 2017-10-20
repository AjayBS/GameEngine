#include "Engine.h"
#include "TIming.h"
#include "Input.h"
#include"GLib.h"
#include "../Externals/lua/lua.hpp"
#include "StringPool.h"
#include "PooledString.h"
#include "ListObjects.h"
#include "Actor.h"
#include "Collision.h"
#include "FileProcess.h"
#include<vector>
#include <functional>


//#include "GLib.h"
namespace Engine {
	HeapManager * pHeapManager;
	void * pHeapMemory;

	
	static ListObjects *listOfObjects;
	static MessagingSystem::MessageHandler *mHandler;

	static Engine::Mutex *mutexForRender;

	HINSTANCE i_hInstance;
	HINSTANCE i_hPrevInstance;
	LPWSTR i_lpCmdLine;
	int i_nCmdShow;

	bool Engine::StartUp(HINSTANCE i_h, HINSTANCE i_hPrev, LPWSTR i_lpCmdL, int i_nCmdS) {
		const size_t sizeHeap = INITIAL_HEAP_SIZE;
		const int numDescriptors = INITIAL_DESCRIPTOR_SIZE;
		pHeapMemory = _aligned_malloc(sizeHeap, DEFAULT_ALIGNMENT);
		pHeapManager = HeapManagerProxy::CreateHeapManager(pHeapMemory, sizeHeap, numDescriptors);
		HeapManagerProxy::SetHeapManager(pHeapManager);
		listOfObjects = new ListObjects();

		mHandler = new MessagingSystem::MessageHandler();
		mutexForRender = new Mutex();
		Profile::SetProfiler();
	//	Profile::GetProfiler() = new Profile::Profiler();


		i_hInstance = i_h;
		i_hPrevInstance = i_hPrev;
		i_lpCmdLine = i_lpCmdL;
		i_nCmdShow = i_nCmdS;

	//	Engine::JobSystem::CreateQueue("Default", 2);

		return pHeapManager != NULL ? true:false;
	}

	bool Engine::ShutDown() {
		_aligned_free(pHeapMemory);
		return true;
	}

	void Engine::Run() {
	
			bool bQuit = false;
					do
					{
						float dt = Timing::CalcLastFrameTime_ms();
						Input::Read();
						// We need to let GLib do it's thing. 
						GLib::Service(bQuit);
					
						if (!bQuit)
						{
							// Tell GLib that we want to start rendering
							GLib::BeginRendering();
							// Tell GLib that we want to render some sprites
							GLib::Sprites::BeginRendering();
							//ConsolePrint("%d", Engine::listOfObjects->listOfActors.capacity());
							if (Engine::listOfObjects->listOfActors.size() == 6)
							{
								Point2 velocity = Point2(0, 0);
								//static GLib::Point2D	Offset = { -180.0f, -100.0f };
								//Offset.x += moveDir;
								//goodGuyObject->SetVelocity(Point2(0, 0));
								if (Input::GetKeyPressed()) {
									// Press I
									Input::Update();
									
								}

								else {		
									for (StrongPointer<Actor> pActor : Engine::GetListOfObjects().listOfActors) {
										if(std::strcmp(pActor->GetGameObject()->GetName(), "first_paddle") == 0 || std::strcmp(pActor->GetGameObject()->GetName(), "second_paddle") == 0)
											pActor->GetGameObject()->SetVelocity(Vector3(0, 0, 0));
										//Engine::listOfObjects->listOfActors.at(1)->GetGameObject()->SetVelocity(Vector3(0, 0, 0));
									}
									
								}							

									bool gameOverState = Physics::Update(dt);
									if (gameOverState)
										bQuit = true;
									Renderer::Draw();									
							}
								// Tell GLib we're done rendering sprites
								GLib::Sprites::EndRendering();
								// Tell GLib we're done rendering
								GLib::EndRendering();
						}
					} while (bQuit == false);
					if (Profile::GetProfiler().m_AllAccumulators.size() > 0) {
						#ifdef ENABLE_PROFILING
						auto key = Profile::GetProfiler().m_AllAccumulators.find("CheckCollision");// = Profile::GetProfiler().m_AllAccumulators.find("CheckCollision");
						#endif
																								   //ConsolePrint("%lf is the average", key->second->average());
					}
					if (Engine::GetListOfObjects().listOfActors.at(0)->completelyLoaded) {
						GLib::Sprites::Release(Engine::listOfObjects->listOfRenderedActors.at(0)->sprite);			
				
					}
					if (Engine::GetListOfObjects().listOfActors.at(1)->completelyLoaded) {
						GLib::Sprites::Release(Engine::listOfObjects->listOfRenderedActors.at(1)->sprite);
					}
					if (Engine::GetListOfObjects().listOfActors.at(2)->completelyLoaded) {
						GLib::Sprites::Release(Engine::listOfObjects->listOfRenderedActors.at(2)->sprite);
					}
					if (Engine::GetListOfObjects().listOfActors.at(3)->completelyLoaded) {
						GLib::Sprites::Release(Engine::listOfObjects->listOfRenderedActors.at(3)->sprite);
					}
					if (Engine::GetListOfObjects().listOfActors.at(4)->completelyLoaded) {
						GLib::Sprites::Release(Engine::listOfObjects->listOfRenderedActors.at(4)->sprite);
					}
					if (Engine::GetListOfObjects().listOfActors.at(5)->completelyLoaded) {
					#ifdef _DEBUG
						GLib::Sprites::Release(Engine::listOfObjects->listOfRenderedActors.at(5)->sprite);
					#endif // _RELEASE						
					}
					//if (pBadGuy)
					//GLib::Sprites::Release(pBadGuy);
					GLib::Shutdown();
	}

	void CreateActor(const char * i_pLuaFilename)
	{
		if (i_pLuaFilename)
		{
			size_t sizeFileContents = 0;
			uint8_t * pFileContents = Engine::LoadFile(i_pLuaFilename, sizeFileContents);

			if (pFileContents && sizeFileContents)
			{
				/*IJob * pProcessJob = new ProcessFile_Process(pFileContents, sizeFileContents);
				assert(!pProcessJob);*/				
					//Engine::GetMutexForRender().Acquire();
					lua_State * pLuaState = luaL_newstate();
					assert(!pLuaState);
					Actor *pActor;
					float		Position[3] = { 0.0f };
					float Sprite_Offset[2] = { 0.0f };
					float Sprite_Extents[2] = { 0.0f };
					luaL_openlibs(pLuaState);

					// Read in a file
					size_t	sizeFile = 0;
					char * pName = new char[100];
					int			result = 0;

					// Do the initial buffer parsing
					result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *>(pFileContents), sizeFileContents, nullptr);
					assert(result != 0);
					lua_pcall(pLuaState, 0, 0, 0);
					assert(result != 0);

					int	type = LUA_TNIL;

					// Find the global variable named "Player" and push it onto stack.
					// If it doesn't find it it pushes a nil value instead
					result = lua_getglobal(pLuaState, "Character");
					assert(result != LUA_TTABLE);
					{
						// Get the Actor name from the Player table
						// 1. Push the key string
						lua_pushstring(pLuaState, "name");
						// 2. Get the value associated with the key
						type = lua_gettable(pLuaState, -2);
						assert(type != LUA_TSTRING);

						//memcpy_s(pName, lua_tostring(pLuaState, -1), 100);
						//pName = lua_tostring(pLuaState, -1);
						strcpy_s(pName, 100, lua_tostring(pLuaState, -1));
						assert(pName == NULL);

						/*if (pName)
						pName = _strdup(pName);*/

						// 3. Remove the value from the stack now that we're done with it
						lua_pop(pLuaState, 1);
					}


					lua_pushstring(pLuaState, "sprite");
					type = lua_gettable(pLuaState, -2);
					assert(type != LUA_TSTRING);
					char *spriteLocation = new char[100];
					strcpy_s(spriteLocation, 100, lua_tostring(pLuaState, -1));

					lua_pop(pLuaState, 1);

					// let's process the "render_settings" sub table
					lua_pushstring(pLuaState, "render_settings");
					type = lua_gettable(pLuaState, -2);

					if (type == LUA_TTABLE)
					{
						lua_pushstring(pLuaState, "spriteName");
						type = lua_gettable(pLuaState, -2);
						assert(!(type == LUA_TTABLE));
						{
							lua_pushstring(pLuaState, "offset");
							type = lua_gettable(pLuaState, -2);
							assert(!(type == LUA_TTABLE));

							//Sprite_Offset[2] = { 0.0f };
							Engine::ReadFloatArray(pLuaState, -1, Sprite_Offset, 2);

							// pop "offset" table
							lua_pop(pLuaState, 1);

							lua_pushstring(pLuaState, "extents");
							type = lua_gettable(pLuaState, -2);
							assert(!(type == LUA_TTABLE));


							//float Sprite_Extents[2] = { 0.0f };
							Engine::ReadFloatArray(pLuaState, -1, Sprite_Extents, 2);

							// pop "extents" table
							lua_pop(pLuaState, 1);


						}
						// pop render settings" table
						lua_pop(pLuaState, 1);
					}

					lua_pushstring(pLuaState, "fileLocation");
					type = lua_gettable(pLuaState, -3);
					assert(type != LUA_TSTRING);
					char *fileLocation = new char[100];
					strcpy_s(fileLocation, 100, lua_tostring(pLuaState, -1));
					lua_pop(pLuaState, 1);

					// Get the Actors name from the Player table
					lua_pushstring(pLuaState, "initial_position");
					type = lua_gettable(pLuaState, -3);
					assert(type != LUA_TTABLE);


					Engine::ReadFloatArray(pLuaState, -1, Position, 3);

					// we're done with the "initial_position table - pop it
					lua_pop(pLuaState, 1);

					lua_close(pLuaState);
					GameObject *obj = new GameObject((char *)pName, Vector3(Position[0], Position[1], Position[2]));
					pActor = new Actor(obj);
					StrongPointer<Actor> pGuy(pActor);
					Engine::GetListOfObjects().pushActors(pGuy);

					Renderer::RendererInfo *goodGuyRender = new Renderer::RendererInfo(pGuy);
					Physics::PhysicsInfo *goodGuyPhysics = new Physics::PhysicsInfo(pGuy);
					//GLib::Sprites::Sprite * pGoodGuySprite = CreateSprite("data\\GoodGuy.dds");
					goodGuyRender->sprite = goodGuyRender->CreateSprite(spriteLocation);
					goodGuyRender->CreateBoundingBox(Sprite_Offset, Sprite_Extents);
					goodGuyPhysics->CreatePhysicsData(fileLocation);
					pGuy->GetGameObject()->SetVelocity(Vector3(-0.0045f, 0, 0));
					StrongPointer<Renderer::RendererInfo> renderInfo(goodGuyRender);
					StrongPointer<Physics::PhysicsInfo> physicsInfo(goodGuyPhysics);
					Engine::GetListOfObjects().pushRenderedActors(goodGuyRender);
					//Engine::GetListOfObjects().pushFinishedActors(pGuy);
					Engine::GetListOfObjects().pushPhysicsActors(goodGuyPhysics);
					pGuy->completelyLoaded = true;

					Engine::GetMessageHandler().SendMessageDetail("PlayerBorn", "hello");
				
				}
			}
		}


	uint8_t * Engine::LoadFile(const char * i_pFilename, size_t & o_sizeFile)
	{
		assert(!(i_pFilename != NULL));
		DEBUG_CONSOLE("In load file method\n");
		FILE *				pFile = NULL;

		errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
		if (fopenError != 0)
			return NULL;

		assert(!(pFile != NULL));

		int FileIOError = fseek(pFile, 0, SEEK_END);
		assert(!(FileIOError == 0));

		long FileSize = ftell(pFile);
		assert(!(FileSize >= 0));

		FileIOError = fseek(pFile, 0, SEEK_SET);
		assert(!(FileIOError == 0));

		uint8_t * pBuffer = new uint8_t[FileSize];
		assert(!pBuffer);

		size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
		assert(!(FileRead == FileSize));

		fclose(pFile);

		o_sizeFile = FileSize;

		return pBuffer;
	}

	ListObjects & GetListOfObjects()
	{
		return *listOfObjects;
	}

	MessagingSystem::MessageHandler& GetMessageHandler()
	{
		return *mHandler;
	}

	Engine::Mutex& GetMutexForRender()
	{
		return *mutexForRender;
	}

	
	size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats)
	{
		assert(!i_pState);
		assert(!(lua_gettop(i_pState) >= -i_index));
		assert(!(lua_type(i_pState, i_index) == LUA_TTABLE));

		size_t				index = 0;

		lua_pushnil(i_pState);

		while (lua_next(i_pState, i_index - 1) != 0)
		{
			if (lua_type(i_pState, -1) == LUA_TNUMBER)
			{
				o_pFloats[index] = float(lua_tonumber(i_pState, -1));
			}
			else
			{
				// DEBUG_PRINT( "Expected a number at position %d while reading table as float array.\n", index );
			}

			// pop the value now that we've retrieved it
			lua_pop(i_pState, 1);
			if (++index == i_numFloats)
			{
				lua_pop(i_pState, 1);
				break;
			}
		}
		return index;
	}


	


}

