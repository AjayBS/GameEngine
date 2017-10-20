#include "Collision.h"
#include "Matrix.h"
#include<vector>

namespace Physics {
	namespace Collision
	{
		using namespace Engine;
		using namespace Math;		

		CollisionPair CheckCollision(float dt)
		{	
			PROFILE_UNSCOPED("CheckCollision");
			const size_t count = Engine::GetListOfObjects().listOfActors.size();
			CollisionPair 	EarliestCollision;
			for (size_t i = 0; i < (count - 1); i++) {
				for (size_t j = i + 1; j < count; j++)
				{
					float	colTime = 0;
					Vector3	colNormal;
					
					EarliestCollision.m_CollisionTime = dt;
					
					bool seperation1 = UpdateCollision(Engine::GetListOfObjects().listOfActors.at(i), Engine::GetListOfObjects().listOfActors.at(j), Engine::GetListOfObjects().listOfRenderedActors.at(i), Engine::GetListOfObjects().listOfRenderedActors.at(j), colTime,colNormal, dt);
					
					if (!seperation1) {
						bool seperation2 = UpdateCollision(Engine::GetListOfObjects().listOfActors.at(j), Engine::GetListOfObjects().listOfActors.at(i), Engine::GetListOfObjects().listOfRenderedActors.at(j), Engine::GetListOfObjects().listOfRenderedActors.at(i),colTime,colNormal, dt);
						if (!seperation2) {
							//DEBUG_CONSOLE("%f hello", colNormal.Y());
							
						if (colTime < EarliestCollision.m_CollisionTime)
							{
							//DEBUG_CONSOLE("Check Collided between %s and %s\n", Engine::GetListOfObjects().listOfActors.at(i)->GetGameObject()->GetName(), Engine::GetListOfObjects().listOfActors.at(j)->GetGameObject()->GetName());
							//DEBUG_CONSOLE("Check CollidedABC\n");
								EarliestCollision.m_CollisionTime = colTime;
								EarliestCollision.m_CollisionNormal = colNormal;
								EarliestCollision.m_CollisionObjects[0] = Engine::GetListOfObjects().listOfActors.at(i)->GetGameObject();
								EarliestCollision.m_CollisionObjects[1] = Engine::GetListOfObjects().listOfActors.at(j)->GetGameObject();
								EarliestCollision.collided = true;
							}
							// Get direction
							//float x = Engine::GetListOfObjects().listOfActors.at(i)->GetGameObject()->GetPosition().X() - 100.0f;
							//Engine::GetListOfObjects().listOfActors.at(i)->GetGameObject()->SetPosition(Vector3(x, Engine::GetListOfObjects().listOfActors.at(i)->GetGameObject()->GetPosition().Y(), Engine::GetListOfObjects().listOfActors.at(i)->GetGameObject()->GetPosition().Z()));
							EarliestCollision.collided = true;
						}
						else
							EarliestCollision.collided = false;
					}
					else
						EarliestCollision.collided = false;
				}
			}
		
			return EarliestCollision;
		}

		bool UpdateCollision(StrongPointer<Actor> player1, StrongPointer<Actor> player2, StrongPointer<Renderer::RendererInfo> renderActor1, StrongPointer<Renderer::RendererInfo> renderActor2, float & o_CollisionTime, Vector3 & o_CollisionNormal, float dt)
		{
			
			Vector4 NormalInWorld;
			Vector4 YNormalInWorld;

			float collisionOffsetX = 0.0f, collisionOffsetY = 0.0f;
			//for player 1
			Matrix mRot1 = mRot1.CreateZRotation(0);
			Matrix mTrans1 = mTrans1.CreateTranslation(player1->GetGameObject()->GetPosition());
			Matrix mP1toWorld = mTrans1*mRot1;

			//for player2
			Matrix mRot2 = mRot2.CreateZRotation(0);
			Matrix mTrans2 = mTrans2.CreateTranslation(player2->GetGameObject()->GetPosition());
			Matrix mP2toWorld = mTrans2 * mRot2;
			Matrix mWorldtoP2 = mP2toWorld.GetInverse();

			//P1 to P2
			Matrix mP1ToP2 = mWorldtoP2*mP1toWorld;

			//
			Vector4 P2xInWorld = mP2toWorld * Vector4(1.0f, 0.0f, 0.0f, 0.0f);
			Vector4 P1xInWorld = mP1toWorld * Vector4(1.0f, 0.0f, 0.0f, 0.0f);

			Vector4 P2yInWorld = mP2toWorld * Vector4(0.0f, 1.0f, 0.0f, 0.0f);
			Vector4 P1yInWorld = mP1toWorld * Vector4(0.0f, 1.0f, 0.0f, 0.0f);

			


			//Checking Seperation in Player2 

			Vector4 test = Vector4(renderActor1->bb.Center.X(), renderActor1->bb.Center.Y(), renderActor1->bb.Center.Z(), 1.0f);
			Vector4 P1CenterInP2 = mP1ToP2 * test;
			Vector4 P1ExtendsXinP2 = mP1ToP2 * Vector4(renderActor1->bb.Extents.X(), 0.0f, 0.0f, 0.0f);
			Vector4 P1ExtendsYinP2 = mP1ToP2 * Vector4(0.0f, renderActor1->bb.Extents.Y(), 0.0f, 0.0f);

			//Relative Velocity
			Vector3 VelP1RelToP2 = player1->GetGameObject()->GetVelocity() - player2->GetGameObject()->GetVelocity();
			Vector4 VelP1InP2 = mWorldtoP2 * Vector4(VelP1RelToP2.X(), VelP1RelToP2.Y(), VelP1RelToP2.Z(), 0.0f);

			//for x axis
			float P1ProjectionOntoP2_X = fabs(P1ExtendsXinP2.X()) + fabs(P1ExtendsYinP2.X());
			float P2ExtentsX = renderActor2->bb.Extents.X() + P1ProjectionOntoP2_X;
			float P2LeftX = renderActor2->bb.Center.X() - P2ExtentsX;
			float P2RightX = renderActor2->bb.Center.X() + P2ExtentsX;

			float DCloseX = P2LeftX - P1CenterInP2.X();
			float DOpenX = P2RightX - P1CenterInP2.X();

			float tCloseX = DCloseX / VelP1InP2.X();
			float tOpenX = DOpenX / VelP1InP2.X();
			int flagZeroVelocityX = 0;

			bool SeperatedX = false;
			
			if ((VelP1InP2.X() == 0)) {
				flagZeroVelocityX = 1;
				if (P2LeftX <= P1CenterInP2.X() && P2RightX >= P1CenterInP2.X())
				{					
					//there is overlap in axis but still need to check seperation in other axis
				}
				else {
					//there is never gonna be collision in either axis
					return true;
				}

			}
			//tOpen and tClose logic for X axis
			if (tCloseX > dt) {
				// Ignore all collision checks for separation X
			}
			else {
				if (tOpenX < tCloseX) {
					float swapValue = tOpenX;
					tOpenX = tCloseX;
					tCloseX = swapValue;
				}
			}
			if (flagZeroVelocityX == 0) {
				if (tOpenX < tCloseX) {
					collisionOffsetX = -1.0f;
					float tempTime;
					tempTime = tOpenX;
					tOpenX = tCloseX;
					tCloseX = tempTime;
					//swap topen and tclose
				}
				if (tOpenX < 0) {
					SeperatedX = true;
					//Collision occured in past and there is not collision for entire frame
				}

				if (tCloseX > dt) // Seperation will close after this frame so THERE IS no collision in this frame
				{
					SeperatedX = true;
				}

				if (collisionOffsetX != -1.0f && SeperatedX == false) {
					collisionOffsetX = 1.0f;
				}
			}
			//bool SeperatedY = false; //= fabs(P1CenterInP2.GetX() - Player2->GetBB().Center.GetX()) > (Player2->GetBB().Extends.GetX() + P1ProjectionOntoP2_X );

			//for y axis on to P2
			float P1ProjectionOntoP2_Y = fabs(P1ExtendsXinP2.Y()) + fabs(P1ExtendsYinP2.Y());
			float P2ExtentsY = renderActor2->bb.Extents.Y() + P1ProjectionOntoP2_Y;
			float P2LeftY = renderActor2->bb.Center.Y() - P2ExtentsY;
			float P2RightY = renderActor2->bb.Center.Y() + P2ExtentsY;

			int flagZeroVelocityY = 0;
			if ((VelP1InP2.Y() == 0)) {
				flagZeroVelocityY = 1;
				if (P2LeftY <= P1CenterInP2.Y() && P2RightY >= P1CenterInP2.Y())
				{
					//there is overlap in axis but still need to check seperation in other axis
				}
				else {
					//there is never gonna be collision in either axis
					return true;
				}

			}

			float DCloseY = P2LeftY - P1CenterInP2.Y();
			float DOpenY = P2RightY - P1CenterInP2.Y();

			float tCloseY = DCloseY / VelP1InP2.Y();
			float tOpenY = DOpenY / VelP1InP2.Y();

			bool SeperatedY = false;

			if (tCloseY > dt) {
				// Ignore all collision checks for separation X
			}
			else {
				if (tOpenY < tCloseY) {
					float swapValue;
					swapValue = tOpenY;
					tOpenY = tCloseY;
					tCloseY = swapValue;
				}
			}
			//tOpen and tClose logic for X axis

			if (flagZeroVelocityY == 0) {
				if (tOpenY < tCloseY) {
					collisionOffsetY = -1.0f;
					float tempTime;
					tempTime = tOpenY;
					tOpenY = tCloseY;
					tCloseY = tempTime;
					//swap topen and tclose
				}
				if (tOpenY < 0) {
					SeperatedY = true;
					//Collision occured in past and there is not collision for entire frame
				}

				if (tCloseY > dt) // Seperation will close after this frame so THERE IS no collision in this frame
				{
					SeperatedY = true;
				}

				if (collisionOffsetY != -1.0f && SeperatedY == false) {
					collisionOffsetY = 1.0f;
				}
			}
			if (SeperatedX || SeperatedY)
			{
				//ConsolePrint("%f", player1->GetGameObject()->GetPosition().Y());
				return true;
			}
			float tOpen = tOpenX < tOpenY ? tOpenX : tOpenY;
			Vector3 AlignedAxis;
			// Find latest tClose
			float tClose = tCloseX > tCloseY ? tCloseX : tCloseY;
			if (tCloseX > tCloseY) {
				AlignedAxis = cross(Vector3(P1xInWorld.X(), P1xInWorld.Y(), P1xInWorld.Z()), Vector3(P2xInWorld.X(), P2xInWorld.Y(), P2xInWorld.Z()));
				NormalInWorld = Vector4(-P1xInWorld.X(), P1xInWorld.Y(), 0.0f, 0.0f);
			}
			else {
				AlignedAxis = cross(Vector3(P1yInWorld.X(), P1yInWorld.Y(), P1yInWorld.Z()), Vector3(P2yInWorld.X(), P2yInWorld.Y(), P2yInWorld.Z()));
				NormalInWorld = Vector4(P1yInWorld.X(), -P1yInWorld.Y(), 0.0f, 0.0f);
			}
			//Calculating latest tclose
			Vector4 tempVect;
			if (tOpen > tClose) {
				//there is collision	

				//NormalInWorld = mP2toWorld * Vector4(-AlignedAxis.Y(), AlignedAxis.X(), 0.0f, 0.0f);
				o_CollisionNormal.SetX(NormalInWorld.X());
				o_CollisionNormal.SetY(NormalInWorld.Y());
				o_CollisionNormal.SetZ(NormalInWorld.Z());
				o_CollisionTime = tClose;
				return false;
			}
			else
				return true;
		}
	}
}
