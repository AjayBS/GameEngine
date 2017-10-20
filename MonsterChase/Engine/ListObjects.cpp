#include "ListObjects.h"



ListObjects::ListObjects()
{
	actorMutex.Assign();
	physicsMutex.Assign();
	renderMutex.Assign();
	listOfActors.reserve(100);
	listOfPhysicsActors.reserve(100);
	listOfRenderedActors.reserve(100);
}


ListObjects::~ListObjects()
{
}

std::vector<StrongPointer<Actor>> ListObjects::GetListOfActors()
{
	return listOfActors;
}

std::vector<StrongPointer<Physics::PhysicsInfo>> ListObjects::GetListOfPhysicsActors()
{
	return listOfPhysicsActors;
}

std::vector<StrongPointer<Renderer::RendererInfo>> ListObjects::GetListOfRenderedActors()
{
	return listOfRenderedActors;
}

std::vector<StrongPointer<Actor>> ListObjects::GetListOfFinishedActors()
{
	return listOfFinishedActors;
}

std::vector<StrongPointer<Actor>> ListObjects::GetListOfActorsInOrder()
{
	return std::vector<StrongPointer<Actor>>();
}

void ListObjects::SetListOfActorsInOrder()
{
	for (StrongPointer<Physics::PhysicsInfo> physics : listOfPhysicsActors) {
		StrongPointer<Actor> pActor = physics->m_pObject.Acquire();
	}
}

void ListObjects::pushActors(StrongPointer<Actor> actor)
{
	actorMutex.Acquire();
	listOfActors.push_back(actor);
	actorMutex.Release();
}



void ListObjects::pushRenderedActors(StrongPointer<Renderer::RendererInfo> actor)
{
	renderMutex.Acquire();
	listOfRenderedActors.push_back(actor);
	renderMutex.Release();
}

void ListObjects::pushPhysicsActors(StrongPointer<Physics::PhysicsInfo> actor)
{
	physicsMutex.Acquire();
	listOfPhysicsActors.push_back(actor);
	physicsMutex.Release();
}



