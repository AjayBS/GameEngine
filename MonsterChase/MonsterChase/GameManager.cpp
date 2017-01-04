#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::InitializeGameObjects(HeapManager *heap) {
	pHeapManager = heap;
	player = InitializePlayer();
	myint_t count = pHeapManager->ShowFreeBlocks();
	GetNumberOfMonsters();
	monsters = GenerateMonsters();
	count = pHeapManager->ShowFreeBlocks();
	
}

PlayerController* GameManager::InitializePlayer() {
	PlayerController *player = new PlayerController();
	player->InitializePlayer();
	myint_t count = pHeapManager->ShowFreeBlocks();
	return player;
}

void GameManager::GetNumberOfMonsters() {
	printf_s("ENTER NO OF MONSTERS::");
	scanf_s("%d", &noOfMonsters);
	if (noOfMonsters == VALUE_ZERO || noOfMonsters < VALUE_ZERO) {
		GetNumberOfMonsters();
	}

}

MonsterController* GameManager::GenerateMonsters() {
	MonsterController *monsterController = new MonsterController();
	//	myint_t count = heap.ShowFreeBlocks();	
	monsterController->InitializeMonsters(noOfMonsters);
	return monsterController;
}
