#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
namespace cg
{
	void cg::SpriteComponent::Update(float dt)
	{

	}

	void cg::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform.position.x, m_owner->m_transform.position.y, cg::Rad2Deg(m_owner->m_transform.rotation));
	}
}
