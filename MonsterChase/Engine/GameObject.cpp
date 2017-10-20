#include "GameObject.h"


Point2 GameObject::GetPosition() const
{
	return Point2();
}

void GameObject::SetVelocity(Point2 & i_Velocity)
{
	m_Velocity = i_Velocity;
}

Point2 GameObject::GetVelocity()
{
	return m_Velocity;
}

void GameObject::SetPosition(Point2 & i_Position)
{
	m_Position = i_Position;
}

void GameObject::SetName(char *name) {
	int i = 0;
	for (i = 0; i < name[i] != '\0'; i++) {
		o_name[i] = name[i];
	}
	o_name[i] = '\0';
	m_Name = o_name;
}

char* GameObject::GetName() {
	return m_Name;
}