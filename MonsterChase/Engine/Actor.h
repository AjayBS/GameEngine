#pragma once
#include "GameObject.h"
#include "HashedString.h"

class Actor
{
public:
	Actor();
	Actor(GameObject *ipObject);
	~Actor();

	GameObject* GetGameObject();
	bool completelyLoaded = false;
	int lives = 3;

	void HandlePlayerBorn(const Engine::HashedString & i_Message) {
		DEBUG_CONSOLE("Player is born:.\n");
	}
private:
	GameObject *mpObject;
};

