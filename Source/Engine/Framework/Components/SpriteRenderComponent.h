#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"
namespace cg
{
	class SpriteRenderComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(SpriteRenderComponent);
		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer);
		

	public:
		Rect source;
		std::string textureName;
		res_t<Texture> m_texture;
		bool flipH = false;
		Vector2 origin{0.5f, 0.5f};
	};
}