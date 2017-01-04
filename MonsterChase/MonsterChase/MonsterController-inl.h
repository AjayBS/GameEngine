#pragma once
inline void MonsterController::DisplayPosition() const{
	for (int i = 0; i < numOfMonsters;i++) {
		printf("Monster %s is at [%.2f][%.2f]\n", monsterObjects->at(i).GetName(), monsterObjects->at(i).GetPosition().GetPositionX(), monsterObjects->at(i).GetPosition().GetPositionY());

	}
}

inline void MonsterController::Move() {
	UpdateGameObject();
	/*position.SetPositionX((float)Random(0, 100));
	position.SetPositionY((float)Random(0, 100));*/
}