#pragma once
#include "Engine.h"
#include "Point2.h"

namespace Physics {
	namespace Collision
	{
		struct CollisionPair
		{
			float		m_CollisionTime = 0.0f;
			Vector3	m_CollisionNormal;
			GameObject *	m_CollisionObjects[2];
			bool collided = false;
		};
		CollisionPair CheckCollision(float dt);
		bool UpdateCollision(StrongPointer<Actor> player1, StrongPointer<Actor> player2, StrongPointer<Renderer::RendererInfo> renderActor1, StrongPointer<Renderer::RendererInfo> renderActor2, float & o_CollisionTime, Vector3 & o_CollisionNormal, float dt);
	}
}

