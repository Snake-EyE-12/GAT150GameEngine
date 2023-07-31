#include "Bullet.h"
#include "Framework/Scene.h"
#include "AstroidFighter.h"

void Bullet::Update(float dt)
{
	Actor::Update(dt);

	cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * dt;

	m_transform.position.x = cg::Wrap(m_transform.position.x, (float)cg::g_renderer.getWidth());
	m_transform.position.y = cg::Wrap(m_transform.position.y, (float)cg::g_renderer.getHeight());
}

void Bullet::OnCollision(Actor* other)
{
	if (other->m_tag != "Enemy" && other->m_tag != "Laser") {
		m_destroyed = true;
		if (other->m_tag == "Block") m_game->AddPoints(1);
	}
}
