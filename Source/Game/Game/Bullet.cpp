#include "Bullet.h"
#include "Framework/Scene.h"
#include "AstroidFighter.h"
#include "Renderer/Renderer.h"
namespace cg
{
	CLASS_DEFINITION(Bullet);
	bool Bullet::Initialize()
	{
		Actor::Initialize();
		m_physicsComponent = GetComponent<PhysicsComponent>();
		return true;
	}

	void Bullet::OnDestroy()
	{
	}

	void Bullet::Update(float dt)
	{
		Actor::Update(dt);

		cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(transform.rotation);
		m_physicsComponent->SetVelocity(forward * m_speed);

		transform.position.x = cg::Wrap(transform.position.x, (float)cg::g_renderer.getWidth());
		transform.position.y = cg::Wrap(transform.position.y, (float)cg::g_renderer.getHeight());
	}

	void Bullet::OnCollisionEnter(Actor* other)
	{
		/*if (other->tag != "Enemy" && other->tag != "Laser") {
			m_destroyed = true;
			if (other->tag == "Block") m_game->AddPoints(1);
		}*/
	}
	void Bullet::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_NAME_DATA(value, "speed", m_speed);
	}
}