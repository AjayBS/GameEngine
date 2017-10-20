#include "FileProcess.h"

namespace Engine {

void ProcessFile::Run()
{
	DEBUG_CONSOLE("In Process file Run method\n");
	if (m_pFilename)
	{
		size_t sizeFileContents = 0;
		uint8_t * pFileContents = LoadFile(m_pFilename, sizeFileContents);

		if (pFileContents && sizeFileContents)
		{
			IJob * pProcessJob = new ProcessFile_Process(pFileContents, sizeFileContents);
			assert(!pProcessJob);

			Engine::JobSystem::RunJob(*pProcessJob, "Default");
		}
	}
}

uint8_t * ProcessFile::LoadFile(const char * i_pFilename, size_t & o_sizeFile)
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

void ProcessFile_Process::Run()
{
	
	if (m_sizeFileContents  && m_pFileContents)
	{
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
		result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *>(m_pFileContents), m_sizeFileContents, nullptr);
		assert(result != 0);
		lua_pcall(pLuaState, 0, 0, 0);
		assert(result != 0);

		int			type = LUA_TNIL;

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
			lua_pushstring(pLuaState, "sprite");
			type = lua_gettable(pLuaState, -2);
			assert(!(type == LUA_TTABLE));
			{
				lua_pushstring(pLuaState, "offset");
				type = lua_gettable(pLuaState, -2);
				assert(!(type == LUA_TTABLE));

				//Sprite_Offset[2] = { 0.0f };
				ReadFloatArray(pLuaState, -1, Sprite_Offset, 2);

				// pop "offset" table
				lua_pop(pLuaState, 1);

				lua_pushstring(pLuaState, "extents");
				type = lua_gettable(pLuaState, -2);
				assert(!(type == LUA_TTABLE));


				//float Sprite_Extents[2] = { 0.0f };
				ReadFloatArray(pLuaState, -1, Sprite_Extents, 2);

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
		strcpy_s(fileLocation,100, lua_tostring(pLuaState, -1));
		lua_pop(pLuaState, 1);

		// Get the Actors name from the Player table
		lua_pushstring(pLuaState, "initial_position");
		type = lua_gettable(pLuaState, -3);
		assert(type != LUA_TTABLE);


		ReadFloatArray(pLuaState, -1, Position, 3);

		// we're done with the "initial_position table - pop it
		lua_pop(pLuaState, 1);
		
		lua_close(pLuaState);
		GameObject *obj = new GameObject((char *)pName, Vector3(Position[0], Position[1],Position[2]));
		pActor = new Actor(obj);
		StrongPointer<Actor> pGuy(pActor);
		Engine::GetListOfObjects().pushActors(pGuy);

		Renderer::RendererInfo *goodGuyRender = new Renderer::RendererInfo(pGuy);
		Physics::PhysicsInfo *goodGuyPhysics = new Physics::PhysicsInfo(pGuy);
		//GLib::Sprites::Sprite * pGoodGuySprite = CreateSprite("data\\GoodGuy.dds");
		goodGuyRender->sprite = goodGuyRender->CreateSprite(spriteLocation);
		goodGuyRender->CreateBoundingBox(Sprite_Offset, Sprite_Extents);
		goodGuyPhysics->CreatePhysicsData(fileLocation);
		

		//Engine::GetListOfObjects().pushRenderedActors(goodGuyRender);
		//Engine::GetListOfObjects().pushFinishedActors(pGuy);
		//Engine::GetListOfObjects().pushPhysicsActors(goodGuyPhysics);
		pGuy->completelyLoaded = true;

		Engine::GetMessageHandler().SendMessageDetail("PlayerBorn","hello");
		//Engine::GetMutexForRender().Release();
	}
	
}

}