#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include "HeapManager.h"
#include "IGameObjectController.h"
#include "PlayerController.h"
#include "MonsterController.h"

class GameManager : public IGameObjectController
{
public:
	GameManager();
	~GameManager();
	void SetGameObject(GameObject *i_pObject) override {
		mainObject = i_pObject;
	};

	void UpdateGameObject() override {
		int count = VALUE_ONE;
		int temp = noOfMonsters;
		bool correctKey = false;
		bool monsterAdd = false;
		do {
			printf_s("Press A to move left, D to move right, W to move up, S to move down or Q to quit\n");
			player->SetCurrentKeyPressed(_getch());
			correctKey = player->CheckKeyPressed();

			if (correctKey) {
				player->Move();
				monsters->Move();

				player->DisplayPosition();
				monsters->DisplayPosition();
				if (count % 4 == VALUE_ZERO) {
					if (!monsterAdd) {
						monsters->RemoveMonster();						
					}
					else
					{
						monsters->AddMonster();
					}					
					noOfMonsters -= VALUE_ONE;	
					if (monsters->numOfMonsters == 0) {
						monsterAdd = true;
					}

					if (monsters->numOfMonsters > 4) {
						monsterAdd = false;
					}
				}
				
				count++;
			}
			//ch = getchar();
		} while (player->GetCurrentKeyPressed() != 'q');
	}

	void InitializeGameObjects(HeapManager *heap);
	PlayerController* InitializePlayer();
	void GetNumberOfMonsters();
	MonsterController* GenerateMonsters();

private:	
	GameObject *mainObject;
	int noOfMonsters;
	PlayerController *player;
	MonsterController *monsters;

	HeapManager * pHeapManager;
};

