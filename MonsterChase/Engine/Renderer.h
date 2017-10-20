#pragma once
#include "GameObject.h"
#include "GLib.h"
#include"Actor.h"
#include "WeakPointer.h"
#include "Vector4.h"

namespace Renderer {
struct AABoundingBox
{
	Vector4 Center;
	Vector4 Extents;
};

class RendererInfo
{
public:
	RendererInfo(StrongPointer<Actor> &i_pObject);
	GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
	void CreateBoundingBox(float Sprite_Offset[4],float Sprite_Extents[4]);

	WeakPointer<Actor> m_pObject;
	GLib::Sprites::Sprite *sprite;
	AABoundingBox bb;
	bool renderComplete = false;

};


void Draw();
}

