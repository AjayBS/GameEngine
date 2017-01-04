#include "MonsterController.h"
#include "HeapManager.h"
#include "GameObject.h"

MonsterController::MonsterController() { 
	//SetGameObject(new GameObject(Point2(0,0)));
}
MonsterController::MonsterController(const char *i_Name,const Point2 pt) {
	//SetGameObject(new GameObject(i_Name, pt));
}
MonsterController::~MonsterController() { delete monsterObjects; }

void MonsterController::InitializeMonsters(int noOfMonsters) {
	monsterObjects = new std::vector<GameObject>();
	//monsterObjects = new GameObject[noOfMonsters];
	
	
	numOfMonsters = noOfMonsters;
	monsterObjects->reserve(numOfMonsters * sizeof(GameObject));
	for (int i = 0; i < noOfMonsters; i++) {
		GameObject monster = GameObject();
		monsterObjects->push_back(monster);
		char name[NAME_LENGTH];
		printf_s("Would you like to name monster %d \n", i);
		scanf_s("%s", name, NAME_LENGTH);
		monsterObjects->at(i).SetName(name);
	}
	//SetGameObject(monsterObjects);
}

void MonsterController::RemoveMonster() {	
	monsterObjects->erase(monsterObjects->end() - 1);
	numOfMonsters--;
}

void MonsterController::AddMonster() {
	GameObject monster = GameObject();
	monsterObjects->push_back(monster);
	numOfMonsters++;
	char name[NAME_LENGTH];
	printf_s("Would you like to name the monster \n");
	scanf_s("%s", name, NAME_LENGTH);
	monsterObjects->at(numOfMonsters-1).SetName(name);
	
}



