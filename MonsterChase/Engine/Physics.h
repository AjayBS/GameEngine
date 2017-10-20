#pragma once
#include "GameObject.h"
#include "Actor.h"
#include "Input.h"
#include "Point2.h"
#include "WeakPointer.h"

namespace Physics {
	
	class PhysicsInfo
	{
	public:
		PhysicsInfo(StrongPointer<Actor> &i_pObject);
		PhysicsInfo();
		~PhysicsInfo();
		//Point2 CalculateVelocity(Point2 i_initialVelocity, Point2 i_forces, float dt);		
		void CreatePhysicsData(const char * i_pLuaFilename);
		float m_Mass;
		float m_Drag;
		float constantForce;
		Vector3 drivingForce = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 directionVector;
		Vector3 nextPosition;
		Vector3 previousPosition;
		WeakPointer<Actor> m_pObject;
		bool keyPressed = false;
	};


	bool Update(float i_dt);
	void Run(float dt);
	Vector3 CalculateVelocity(PhysicsInfo &i_InitialVelocity, Vector3 &i_forces, float i_dt);
	//Point2 GetDragForce(PhysicsInfo &i_pPhysicsInfo, Point2 i_pDrivingForce);
	//void CalculateVelocity(PhysicsInfo &i_initialVelocity, Point2 &i_forces, float dt);

}

