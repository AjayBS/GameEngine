#pragma once
#include <functional>
#include <map>
#include "HashedString.h"

using namespace Engine;

namespace MessagingSystem
{
	class IMessageHandler
	{
	public:
		~IMessageHandler() {}
		virtual void HandleMessage(const HashedString & i_Message) = 0;
	};

	class MessageHandler
	{
		std::map<HashedString, std::function<void(const HashedString &)>> hashTable;
		//std::map<HashedString, JobQueueData *>
	public:
		void RegisterMessageHandler(const HashedString & i_Message, std::function<void(const HashedString &)> i_Handler);
		void DeregisterMessageHandler(const HashedString & i_Message, std::function<void(const HashedString &)> i_Handler);
		void SendMessageDetail(const HashedString & i_Message, void * i_pMessageDetails);
	};



	// Declare a type for a Message Handler
	typedef void(*MessageHandler_t)(const HashedString & i_Message);

	/*void RegisterMessageHandler(const HashedString & i_Message, MessageHandler_t i_pHandler);
	void SendMessage(const HashedString & i_Message, void * i_pMessageDetails);
	void DeregisterMessageHandler(const HashedString & i_Message, IMessageHandler * i_pHandler);*/

}
