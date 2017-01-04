#pragma once
#include<string>
#include "Point2.h"
#include "Maths.h"
#include "IGameObjectController.h"
#include "Macros.h"
#include<vector>

class MonsterController: public IGameObjectController
{
public:
	MonsterController();
	MonsterController(const char *i_Name,const Point2 pt);
	~MonsterController();

	void InitializeMonsters(int noOfMonsters);
	void RemoveMonster();
	void AddMonster();
	inline void Move();
	inline void DisplayPosition() const;
	//inline void SetPosition();

	void SetGameObject(GameObject *i_pObject) override {
		//monsterObjects = i_pObject;
	};

	void UpdateGameObject() override {
		for(int i=0; i<numOfMonsters;i++)
			monsterObjects->at(i).SetPosition(Point2((float)Random(MIN_POSITION_VALUE, MAX_POSITION_VALUE), (float)Random(MIN_POSITION_VALUE, MAX_POSITION_VALUE)));
	}

	int numOfMonsters;
private:
	char name[NAME_LENGTH];
	Engine::Point2 position;
	
	std::vector<GameObject> *monsterObjects;
};

#include "MonsterController-inl.h"