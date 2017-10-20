#include "Messaging.h"

void MessagingSystem::MessageHandler::RegisterMessageHandler(const HashedString & i_Message, std::function<void(const HashedString &)> i_Handler)
{
	//hashTable.
	hashTable.insert(std::pair<HashedString, std::function<void(const HashedString &)>>(i_Message, i_Handler));
	//hashTable.
	//i_Handler(i_Message);
}

void MessagingSystem::MessageHandler::DeregisterMessageHandler(const HashedString & i_Message, std::function<void(const HashedString &)> i_Handler)
{
	std::map<HashedString, std::function<void(const HashedString &)>>::iterator key = hashTable.find(i_Message);
	if (key == hashTable.end()) {
		//handle the error
		DEBUG_CONSOLE("No actor found");
	}
	else {
		delete &(key->second);
		hashTable.erase(key);
	}
}

void MessagingSystem::MessageHandler::SendMessageDetail(const HashedString & i_Message, void * i_pMessageDetails)
{
	std::map<HashedString, std::function<void(const HashedString &)>>::iterator key = hashTable.find(i_Message);
	if (key == hashTable.end()) {
		//handle the error
		DEBUG_CONSOLE("No actor found");
	}
	else {

		key->second(i_Message);
	}
	
}


