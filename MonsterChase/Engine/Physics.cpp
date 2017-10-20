#include "Physics.h"
#include "Engine.h"
#include "Collision.h"
#include "Profiler.h"
#include "Matrix.h"

bool Physics::Update(float i_dt)
{
	using namespace Engine;
	Physics::PhysicsInfo *first_paddle = new Physics::PhysicsInfo();
	Physics::PhysicsInfo *second_paddle = new Physics::PhysicsInfo();
	Physics::PhysicsInfo *ball = new Physics::PhysicsInfo();

	size_t size = Engine::GetListOfObjects().listOfPhysicsActors.size();
	int i = 0;
	for (StrongPointer<Physics::PhysicsInfo> pActor: Engine::GetListOfObjects().listOfPhysicsActors) {
#ifdef _RELEASE
		if (i != size - 1) {
#endif // _RELEASE

		
		Physics::PhysicsInfo &_object_reference = *pActor;
		StrongPointer<Actor> actor(pActor->m_pObject.Acquire());
		Actor *a = actor.GetObjectReference();
		if(a != nullptr) {
		if (strcmp(a->GetGameObject()->GetName(), "first_paddle") == 0)
			first_paddle = &_object_reference;
		else if (strcmp(a->GetGameObject()->GetName(), "second_paddle") == 0)
			second_paddle = &_object_reference;
		else if (strcmp(a->GetGameObject()->GetName(), "ball") == 0)
			ball = &_object_reference;
		}

#ifdef _RELEASE
		}
#endif // _RELEASE
	
		i++;
	}	


	StrongPointer<Actor> m_Object1 = second_paddle->m_pObject.Acquire();

	if (!(m_Object1 == nullptr) && second_paddle->keyPressed) {
		Vector3 finalForce;
		if (second_paddle->drivingForce.X() != 0)
			finalForce.SetX(second_paddle->drivingForce.X() - second_paddle->m_Drag);
		if (second_paddle->drivingForce.Y() != 0)
			finalForce.SetY(second_paddle->drivingForce.Y() - second_paddle->m_Drag);

		Vector3 acceleration = finalForce / second_paddle->m_Mass;

		Vector3 initialVelocity = m_Object1->GetGameObject()->GetVelocity();

		Vector3 finalVelocity = (m_Object1->GetGameObject()->GetVelocity() + acceleration * i_dt);

		Vector3 finalPosition = (m_Object1->GetGameObject()->GetPosition() + ((finalVelocity + initialVelocity) / 2.0f) * i_dt);

		if (finalVelocity.X() <= 0.002f || finalVelocity.Y() <= 0.002f)
			m_Object1->GetGameObject()->SetVelocity(finalVelocity);
		//= io_Object.m_Velocity + Acceleration * i_dt;
		if(finalPosition.Y() <= -265 || finalPosition.Y() >= 130)
			m_Object1->GetGameObject()->SetPosition(m_Object1->GetGameObject()->GetPosition());
		else
		m_Object1->GetGameObject()->SetPosition(finalPosition);

		
	}


	StrongPointer<Actor> m_Object = first_paddle->m_pObject.Acquire();

	if (!(m_Object == nullptr) && first_paddle->keyPressed) {
		Vector3 finalForce;
		if (first_paddle->drivingForce.X() != 0)
			finalForce.SetX(first_paddle->drivingForce.X() - first_paddle->m_Drag);
		if (first_paddle->drivingForce.Y() != 0)
			finalForce.SetY(first_paddle->drivingForce.Y() - first_paddle->m_Drag);

		Vector3 acceleration = finalForce / first_paddle->m_Mass;

		Vector3 initialVelocity = m_Object->GetGameObject()->GetVelocity();

		Vector3 finalVelocity = (m_Object->GetGameObject()->GetVelocity() + acceleration * i_dt);

		Vector3 finalPosition = (m_Object->GetGameObject()->GetPosition() + ((finalVelocity + initialVelocity) / 2.0f) * i_dt);

		if (finalVelocity.X() <= 0.002f || finalVelocity.Y() <= 0.002f)
			m_Object->GetGameObject()->SetVelocity(finalVelocity);
		//= io_Object.m_Velocity + Acceleration * i_dt;
		if (finalPosition.Y() <= -265 || finalPosition.Y() >= 130)
		m_Object->GetGameObject()->SetPosition(m_Object->GetGameObject()->GetPosition());
		else
		m_Object->GetGameObject()->SetPosition(finalPosition);
	}

	StrongPointer<Actor> m_Object2 = ball->m_pObject.Acquire();
//	Vector3 acceleration((ball->directionVector * ball->constantForce) / ball->m_Mass, 0, 0);
	Vector3 initialVelocity = m_Object2->GetGameObject()->GetVelocity();
	ball->nextPosition = m_Object2->GetGameObject()->GetPosition();
	float metric = 1.0f;
	
	
	
	
		Collision::CollisionPair EarliestCollision = Physics::Collision::CheckCollision(i_dt);
		EarliestCollision.m_CollisionObjects[0];
		// Get Velocity VelA' = VelA - 2(VelA.N)N
		if(EarliestCollision.m_CollisionTime > 0.0f) {
		//	ConsolePrint("Check Collided");

		Vector3 initialVelocity = m_Object2->GetGameObject()->GetVelocity();
		Engine::Math::Matrix mVelocityA = mVelocityA.CreateTranslation(m_Object2->GetGameObject()->GetVelocity());
		Vector4 tempVect;
		tempVect.SetX(EarliestCollision.m_CollisionNormal.X());
		tempVect.SetY(EarliestCollision.m_CollisionNormal.Y());
		tempVect.SetZ(EarliestCollision.m_CollisionNormal.Z());
		tempVect.SetW(0);
		Vector4 dotProdTemp = mVelocityA * tempVect;
		Vector3 dotProd;
		dotProd.SetX(dotProdTemp.X());
		dotProd.SetY(dotProdTemp.Y());
		dotProd.SetZ(dotProdTemp.Z());

		

		
		//ConsolePrint("%f", initialVelocity.X());
		Vector3 finalVelocity = dotProd * 2.0f;
		finalVelocity.SetX(EarliestCollision.m_CollisionNormal.X());
		finalVelocity.SetY(EarliestCollision.m_CollisionNormal.Y());
		finalVelocity.SetZ(EarliestCollision.m_CollisionNormal.Z());
		finalVelocity = m_Object2->GetGameObject()->GetVelocity();
		Vector3 postCollisionVelocity = (EarliestCollision.m_CollisionNormal * 2.0f)  * (EarliestCollision.m_CollisionNormal * finalVelocity);
		finalVelocity = (m_Object2->GetGameObject()->GetVelocity() - postCollisionVelocity);
		
		Vector3 finalPosition = (m_Object2->GetGameObject()->GetPosition() + ((finalVelocity + initialVelocity) / 2.0f) * i_dt);
		
		m_Object2->GetGameObject()->SetVelocity(finalVelocity);
		m_Object2->GetGameObject()->SetPosition(finalPosition);
		}
		else {
			if (!(m_Object2 == nullptr)) {
				//ball->directionVector = EarliestCollision.m_CollisionNormal;
				if (m_Object2->GetGameObject()->GetVelocity().X() == 0 && m_Object2->GetGameObject()->GetVelocity().Y() == 0) {
					//finalVelocity = Vector3(-0.0025, 0, 0);
				}
					
				
				Vector3 finalPosition = (m_Object2->GetGameObject()->GetPosition() + ((m_Object2->GetGameObject()->GetVelocity() + initialVelocity) / 2.0f) * i_dt);
				m_Object2->GetGameObject()->SetVelocity(m_Object2->GetGameObject()->GetVelocity());
				m_Object2->GetGameObject()->SetPosition(finalPosition);			

				
				
			}
		}
	
		if (m_Object2->GetGameObject()->GetPosition().X() <= -500 ) {
			DEBUG_CONSOLE("Paddle 2 lives are: %d\n", second_paddle->m_pObject.Acquire()->lives);
			second_paddle->m_pObject.Acquire()->lives--;
			if (second_paddle->m_pObject.Acquire()->lives == -1)
				return true;
			m_Object2->GetGameObject()->SetPosition(Vector3(0, 0, 0));
			m_Object2->GetGameObject()->SetVelocity(Vector3(-0.0045f, 0.0045f, 0));
		}
		if (m_Object2->GetGameObject()->GetPosition().X() >= 500) {
			DEBUG_CONSOLE("Paddle 1 lives are: %d\n", first_paddle->m_pObject.Acquire()->lives);
			first_paddle->m_pObject.Acquire()->lives--;
			if (first_paddle->m_pObject.Acquire()->lives == 0)
				return true;
			m_Object2->GetGameObject()->SetPosition(Vector3(0, 0, 0));
			m_Object2->GetGameObject()->SetVelocity(Vector3(-0.0045f, 0.0045f, 0));
		}
			
		return false;
}

Vector3 Physics::CalculateVelocity(PhysicsInfo & i_InitialVelocity, Vector3 & i_forces, float i_dt)
{
	return Vector3();
}


Physics::PhysicsInfo::PhysicsInfo(StrongPointer<Actor> &i_pObject)
{	
	m_pObject = i_pObject;
	previousPosition = i_pObject.GetObjectReference()->GetGameObject()->GetPosition();
	//Engine::GetListOfObjects().pushPhysicsActors(this);
	
}

Physics::PhysicsInfo::PhysicsInfo()
{
}


void Physics::PhysicsInfo::CreatePhysicsData(const char * i_pLuaFilename)
{
	lua_State * pLuaState = luaL_newstate();
	assert(!pLuaState);

	luaL_openlibs(pLuaState);

	// Read in a file
	size_t	sizeFile = 0;
	void *pFileContents = Engine::LoadFile(i_pLuaFilename, sizeFile);

	if (pFileContents  && sizeFile)
	{
		int			result = 0;

		// Do the initial buffer parsing
		result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
		assert(result != 0);
		lua_pcall(pLuaState, 0, 0, 0);
		assert(result != 0);

		int			type = LUA_TNIL;

		// Find the global variable named "Player" and push it onto stack.
		// If it doesn't find it it pushes a nil value instead
		result = lua_getglobal(pLuaState, "Character");

		lua_pushstring(pLuaState, "physics_settings");
		type = lua_gettable(pLuaState, -2);
		// It either needs to be a table or not there (no physics applied)
		//assert((type == LUA_TNIL) || (type == LUA_TTABLE));

		if (type == LUA_TTABLE)
		{
			lua_pushstring(pLuaState, "mass");
			type = lua_gettable(pLuaState, -2);
			assert(type != LUA_TNUMBER);

			lua_pushstring(pLuaState, "drag");
			type = lua_gettable(pLuaState, -3);
			assert(type != LUA_TNUMBER);

			m_Mass = float(lua_tonumber(pLuaState, -2));
			m_Drag = float(lua_tonumber(pLuaState, -1));

			// pop the "mass" and "drag" values together
			lua_pop(pLuaState, 2);
		}


		lua_pushstring(pLuaState, "constantForce");
		//	// 2. Get the value associated with the key
			type = lua_gettable(pLuaState, -3);
			assert(type != LUA_TNUMBER);
			constantForce = float(lua_tonumber(pLuaState, -1));
			lua_pop(pLuaState, 1);

			lua_close(pLuaState);
		//m_Mass = mass;
	}
}


Physics::PhysicsInfo::~PhysicsInfo()
{
}



