#pragma once

inline void PlayerController::DisplayPosition() const{
	printf("Player %s is at [%.2f][%.2f]\n", name, playerObject->GetPosition().GetPositionX(), playerObject->GetPosition().GetPositionY());
}

inline bool PlayerController::CheckKeyPressed() {
	if (key == 'A' || key == 'a' || key == 'W' || key == 'w' || key == 'S' || key == 's' || key == 'D' || key == 'd') {
		return true;
	}
	return false;
}

inline void PlayerController::InitializePlayer() {
	printf_s("Enter name of player\n");
	scanf_s("%s", name, NAME_LENGTH);

	playerObject->SetPosition(playerObject->GetPosition().zero);
}
