#pragma once
#include<string>
#include "Point2.h"
#include "IGameObjectController.h"
#include "Macros.h"

class PlayerController: public IGameObjectController
{
public:
	PlayerController();
	PlayerController(char *i_Name,const Point2 pt);
	~PlayerController();

	inline void InitializePlayer();
	void Move();
	inline bool CheckKeyPressed();
	inline void DisplayPosition() const;
	void SetCurrentKeyPressed(char key);
	inline char GetCurrentKeyPressed() { return key; };

	void SetGameObject(GameObject *i_pObject) override { 
		playerObject = i_pObject;
	};

	void UpdateGameObject() override {
		switch (key) {
		case 'a': playerObject->SetPosition(playerObject->GetPosition()+playerObject->GetPosition().left);
			break;
		case 'd': playerObject->SetPosition(playerObject->GetPosition() + playerObject->GetPosition().right);
			break;
		case 's': playerObject->SetPosition(playerObject->GetPosition() + playerObject->GetPosition().down);
			break;
		case 'w': playerObject->SetPosition(playerObject->GetPosition() + playerObject->GetPosition().up);
			break;
		}
	}

private:
	char name[NAME_LENGTH];
	/*Engine::Point2 position;*/
	GameObject *playerObject;
	char key;
};

#include "PlayerController-inl.h"