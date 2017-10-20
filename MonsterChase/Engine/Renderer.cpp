#include "Renderer.h"
#include "Engine.h"

void Renderer::Draw()
{
	//RendererInfo & renderer;
	size_t size = Engine::GetListOfObjects().listOfPhysicsActors.size();
	int i = 0;
	for (StrongPointer<Renderer::RendererInfo> renderer : Engine::GetListOfObjects().listOfRenderedActors) {
#ifdef _RELEASE
		if (i != size - 1) {
#endif // RELEASE
			if (renderer->renderComplete) {
				StrongPointer<Actor> obj(renderer->m_pObject.Acquire());

				if (!(obj == nullptr)) {
					GLib::Point2D Offset = { obj->GetGameObject()->GetPosition().X(), obj->GetGameObject()->GetPosition().Y() };
					if (renderer->sprite != nullptr)
						GLib::Sprites::RenderSprite(*renderer->sprite, Offset, 0.0f);
				}
			}
#ifdef _RELEASE
		}
#endif // RELEASE
		i++;
	}

}

Renderer::RendererInfo::RendererInfo(StrongPointer<Actor> &i_pObject)
{
	m_pObject = i_pObject;
	//Engine::GetListOfObjects().pushRenderedActors(this);
	//m_pObject = obj;
}


GLib::Sprites::Sprite * Renderer::RendererInfo::CreateSprite(const char * i_pFilename)
{
	//assert(i_pFilename);
	
	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void * pTextureFile = Engine::LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	//assert(result == true);
	//assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);
	return pSprite;
}


void Renderer::RendererInfo::CreateBoundingBox(float Sprite_Offset[4], float Sprite_Extents[4])
{
	bb.Center = { Sprite_Offset[0] , Sprite_Offset[1], Sprite_Offset[2], Sprite_Offset[3] };
	bb.Extents = { Sprite_Extents[0] , Sprite_Extents[1], Sprite_Extents[2], Sprite_Extents[3] };
	renderComplete = true;
}
