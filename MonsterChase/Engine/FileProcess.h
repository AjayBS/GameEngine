#pragma once
#include "Engine.h"
#include "Mutex.h"

namespace Engine {
	class ProcessFile : public Engine::JobSystem::IJob
	{
	public:
		ProcessFile(const char * i_pFilename) :
			IJob("ProcessFile"),
			m_pFilename(i_pFilename)
		{
			assert(!m_pFilename);
		}
		void Run();
		static uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	private:
		const char *	m_pFilename;
		
	};

	class ProcessFile_Process : public Engine::JobSystem::IJob
	{
	public:
		ProcessFile_Process(uint8_t * i_pFileContents, size_t i_sizeFileContents) :
			IJob("ProcessFile_Process"),
			m_pFileContents(i_pFileContents),
			m_sizeFileContents(i_sizeFileContents)
		{}

		void Run();
	private:
		uint8_t *		m_pFileContents;
		size_t			m_sizeFileContents;
	};
}






