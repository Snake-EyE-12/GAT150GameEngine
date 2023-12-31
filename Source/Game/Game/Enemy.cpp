#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "AstroidFighter.h"

#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Framework/Emitter.h"
#include "Input/InputSystem.h"

#include "Audio/AudioSystem.h"


namespace cg
{
	CLASS_DEFINITION(Enemy);

	bool Enemy::Initialize()
	{
		Actor::Initialize();
		return true;
	}

	void Enemy::OnDestroy()
	{
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);
		m_aliveTime += dt;

		cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(transform.rotation);

		//m_physComp->ApplyTorque(turnAngle);



		//Player* player = m_scene->GetActor<Player>();
		//if (player) {
		//	cg::Vector2 direction = player->m_transform.position - m_transform.position;

		//	float turnAngle = cg::Vector2::SignedAngle(forward, direction.Normalized());

		//	m_transform.rotation += turnAngle * dt;
		//	float angle = cg::Vector2::Angle(forward, direction.Normalized());
		//	if (angle < cg::Deg2Rad(30.0f)) {
		//		// Enemy sees player
		//		if (m_fireTimer <= 0) {
		//			m_fireTimer = m_fireRate;
		//			cg::Transform transform{m_transform.position, m_transform.rotation, 1};
		//			std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(400.0f, transform);
		//			bullet->m_tag = "Bullet";
		//			bullet->m_game = m_game;
		//			//m_scene->Add(std::move(bullet));
		//		}
		//	}
		//}

		transform.position += forward * m_speed * cg::g_time.GetDeltaTime();

		transform.position.x = cg::Wrap(transform.position.x, (float)cg::g_renderer.getWidth());
		transform.position.y = cg::Wrap(transform.position.y, (float)cg::g_renderer.getHeight());

		m_fireTimer -= dt;


	}
	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_NAME_DATA(value, "speed", m_speed);
		READ_NAME_DATA(value, "turnRate", m_turnRate);
		READ_NAME_DATA(value, "fireRate", m_fireRate);
	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		//if (((other->tag == "Block" && !dynamic_cast<Block*>(other)->m_placed) || (other->tag == "Player")) && !m_destroyed) {
		//	m_game->AddPoints(10);
		//	cg::g_audioSystem.PlayOneShot("hit", false);
		//	m_destroyed = true;

		//	//Particles
		//	cg::EmitterData data;
		//	data.burst = true;
		//	data.burstCount = 100;
		//	data.spawnRate = 200;
		//	data.angle = 0;
		//	data.angleRange = cg::Pi;
		//	data.lifetimeMin = 0.5f;
		//	data.lifetimeMax = 1.5f;
		//	data.speedMin = 50;
		//	data.speedMax = 250;
		//	data.damping = 0.5f;
		//	data.color = cg::Color{ cg::randomf(0.5,1), cg::randomf(0,0.5), 0, 1 };

		//	cg::Transform transform{ transform.position, 0, 1 };
		//	auto emitter = std::make_unique<cg::Emitter>(transform, data);
		//	emitter->lifespan = 0.1f;
		//	//m_scene->Add(std::move(emitter));


		//	
		//}

	}
}