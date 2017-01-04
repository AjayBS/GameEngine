#pragma once
#include "Point2.h"
#include<algorithm>
#include<string.h>
class GameObject
{
public:
	GameObject(char *i_pName, const Point2 & i_InitialPosition) :
		m_Name(i_pName),
		m_Position(i_InitialPosition)
	{
	}
	GameObject(const Point2 & i_InitialPosition) :
		m_Name("Default"),
		m_Position(i_InitialPosition)
	{
	}

	GameObject() :
		m_Name("Default"),
		m_Position(Point2(0, 0))
	{

	}
	// copy constructor
	GameObject(const GameObject & i_other) :
		m_Name(_strdup(i_other.m_Name ? i_other.m_Name : "Default")),
		m_Position(i_other.m_Position)
	{   }

	// Move constructor
	GameObject & operator=(const GameObject & i_other) {
		// if we have an existing name release it.
		if (m_Name)
			delete m_Name;
		m_Name = _strdup(i_other.m_Name ? i_other.m_Name : "Default");
		m_Position = i_other.m_Position;
		return *this;
	}

	// move constructor
	GameObject(GameObject && i_other) :
		m_Name(i_other.m_Name),
		m_Position(i_other.m_Position)
	{
		i_other.m_Name = nullptr;
	}
	
	// move assignment operator
	GameObject & operator=(GameObject && i_other)
	{
		std::swap(m_Name, i_other.m_Name);
		std::swap(m_Position, i_other.m_Position);
		return *this;
	}

	// Get / Set our current position
	Point2 GetPosition() const { return m_Position; }
	void SetPosition(Point2 & i_Position) { m_Position = i_Position; }
	void SetName(char *name) {
		int i = 0;
		for (i = 0; i < name[i] != '\0'; i++) {
			o_name[i] = name[i];
		}
		o_name[i] = '\0';
		m_Name = o_name; 
	}
	char* GetName() { return m_Name; }

private:
	char *m_Name;
	char o_name[100];
	Point2	m_Position;
};