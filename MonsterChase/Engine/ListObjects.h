#pragma once
#include"GameObject.h"
#include "Actor.h"
#include "Physics.h"
#include "Renderer.h"
#include "Mutex.h"
#include<vector>
class ListObjects
{
public:
	ListObjects();
	~ListObjects();
	std::vector<StrongPointer<Actor>> GetListOfActors();
	std::vector<StrongPointer<Physics::PhysicsInfo>> GetListOfPhysicsActors();
	std::vector<StrongPointer<Renderer::RendererInfo>> GetListOfRenderedActors();
	std::vector<StrongPointer<Actor>> listOfActors;
	std::vector<StrongPointer<Physics::PhysicsInfo>> listOfPhysicsActors;
	std::vector<StrongPointer<Renderer::RendererInfo>> listOfRenderedActors;
	std::vector<StrongPointer<Actor>> listOfFinishedActors;

	std::vector<StrongPointer<Actor>> GetListOfFinishedActors();
	std::vector<StrongPointer<Actor>> GetListOfActorsInOrder();
	void SetListOfActorsInOrder();

	void pushActors(StrongPointer<Actor> actor);
	void pushRenderedActors(StrongPointer<Renderer::RendererInfo> actor);
	void pushPhysicsActors(StrongPointer<Physics::PhysicsInfo> actor);

	Engine::Mutex actorMutex;
	Engine::Mutex physicsMutex;
	Engine::Mutex renderMutex;
};

