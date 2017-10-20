#include "Input.h"
#include "Engine.h"

namespace Input {
	static bool keyPressed;
	static unsigned int KeyPressValue;
}

void Input::SetKeyPressed(bool changeState, unsigned int key)
{
	KeyPressValue = key;
	Input::keyPressed = changeState;
}

bool Input::GetKeyPressed()
{
	return Input::keyPressed;
}

unsigned int Input::GetKeyValue()
{
	return Input::KeyPressValue;
}

void Input::Read() {
	GLib::SetKeyStateChangeCallback(TestKeyCallback);
}

void Input::Update()
{
	Physics::PhysicsInfo *first_paddle = new Physics::PhysicsInfo();
	Physics::PhysicsInfo *second_paddle = new Physics::PhysicsInfo();
	Physics::PhysicsInfo *ball = new Physics::PhysicsInfo();

	int i = 0;
	size_t size = Engine::GetListOfObjects().listOfPhysicsActors.size();
	for (StrongPointer<Physics::PhysicsInfo> pActor : Engine::GetListOfObjects().listOfPhysicsActors) {
#ifdef _RELEASE
		if (i != size - 1) {
#endif // DEBUG
			Physics::PhysicsInfo &_object_reference = *pActor;
			StrongPointer<Actor> actor = pActor->m_pObject.Acquire();
			Actor *a = actor.GetObjectReference();
			if (a != nullptr) {
				if (strcmp(a->GetGameObject()->GetName(), "first_paddle") == 0)
					first_paddle = &_object_reference;
				else if (strcmp(a->GetGameObject()->GetName(), "second_paddle") == 0)
					second_paddle = &_object_reference;
				else if (strcmp(a->GetGameObject()->GetName(), "ball") == 0)
					ball = &_object_reference;
			}
#ifdef _RELEASE
		}
#endif // DEBUG
		i++;
	}

	//Press I
	if (Input::GetKeyValue() == 0x49) {
		first_paddle->drivingForce.SetX(0);
		first_paddle->drivingForce.SetY(first_paddle->constantForce);
		first_paddle->keyPressed = true;
		//velocity->SetX(drivingForce->GetX() - opposingForce);
		//velocity->SetY(0);
	}
	// Press K
	else if (Input::GetKeyValue() == 0x4b) {
		first_paddle->drivingForce.SetX(0);
		first_paddle->drivingForce.SetY(-first_paddle->constantForce);
		first_paddle->keyPressed = true;
		//velocity->SetX(-(drivingForce->GetX() - opposingForce));
		//velocity->SetY(0);
	}
	else {
		first_paddle->drivingForce.SetX(0);
		first_paddle->drivingForce.SetY(0);
		first_paddle->keyPressed = false;
	}
	// Press W
	if (Input::GetKeyValue() == 0x57) {
		second_paddle->drivingForce.SetX(0);
		second_paddle->drivingForce.SetY(second_paddle->constantForce);
		second_paddle->keyPressed = true;
		//velocity->SetX(0);
		//velocity->SetY(drivingForce->GetY() - opposingForce);
		//goodGuyObject->SetPosition(Point2(10, 10));

	}
	// Press S
	else if (Input::GetKeyValue() == 0x53) {
		second_paddle->drivingForce.SetX(0);
		second_paddle->drivingForce.SetY(-second_paddle->constantForce);
		second_paddle->keyPressed = true;
		//velocity->SetY(-(drivingForce->GetY() - opposingForce));
	}
	else {
		second_paddle->drivingForce.SetX(0);
		second_paddle->drivingForce.SetY(0);
		second_paddle->keyPressed = false;

	}
	
}

void Input::SetStateChange() {
	//GLib::SetKeyStateChangeCallback(TestKeyCallback);
}

void Input::TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "Key %c went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
	if (bWentDown && (i_VKeyID == 0x49 || i_VKeyID == 0x4b || i_VKeyID == 0x57 || i_VKeyID == 0x53)) {
		Input::SetKeyPressed(true, i_VKeyID);
	}
	else {
		Input::SetKeyPressed(false, 0);
	}

}


