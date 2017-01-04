#pragma once
#include "GameObject.h"
class IGameObjectController
{
public:
	virtual void SetGameObject(GameObject *i_pObject) = 0;
	virtual void UpdateGameObject() = 0;
};