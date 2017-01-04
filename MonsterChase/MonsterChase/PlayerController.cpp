#include "PlayerController.h"

PlayerController::PlayerController() {
	SetGameObject(new GameObject(Point2(0, 0)));
}
PlayerController::PlayerController(char *i_Name,const Point2 pt) {
	SetGameObject(new GameObject(i_Name,pt));
}
PlayerController::~PlayerController() { 
	delete playerObject; 
}

void PlayerController::Move() {
	/*switch (key) {
	case 'a': position += position.left;
		break;
	case 'd': position += position.right;
		break;
	case 's': position += position.down;
		break;
	case 'w': position += position.up;
		break;
	}*/
	UpdateGameObject();
}

void PlayerController::SetCurrentKeyPressed(char key) {
	this->key = key;
}

