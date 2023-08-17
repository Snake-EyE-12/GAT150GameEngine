#include "Bullet.h"
#include "Framework/Scene.h"
#include "AstroidFighter.h"
#include "Renderer/Renderer.h"

void Bullet::Update(float dt)
{
	Actor::Update(dt);

	cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(transform.rotation);
	transform.position += forward * m_speed * dt;

	transform.position.x = cg::Wrap(transform.position.x, (float)cg::g_renderer.getWidth());
	transform.position.y = cg::Wrap(transform.position.y, (float)cg::g_renderer.getHeight());
}

void Bullet::OnCollision(Actor* other)
{
	if (other->tag != "Enemy" && other->tag != "Laser") {
		m_destroyed = true;
		if (other->tag == "Block") m_game->AddPoints(1);
	}
}
