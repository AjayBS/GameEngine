#include "Actor.h"
#include "Engine.h"
#include <functional>


Actor::Actor()
{
	Engine::GetMessageHandler().RegisterMessageHandler("PlayerBorn", std::bind(&Actor::HandlePlayerBorn, this, std::placeholders::_1));
}

Actor::Actor(GameObject * ipObject)
{
	mpObject = ipObject;
	Engine::GetMessageHandler().RegisterMessageHandler("PlayerBorn", std::bind(&Actor::HandlePlayerBorn, this, std::placeholders::_1));

	
}


Actor::~Actor()
{
	Engine::GetMessageHandler().DeregisterMessageHandler("PlayerBorn", std::bind(&Actor::HandlePlayerBorn, this, std::placeholders::_1));
}

GameObject * Actor::GetGameObject()
{
	return mpObject;
}
