#include "Player.h"
#include "Input/InputSystem.h"
#include "Enemy.h"
#include "AstroidFighter.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "Bullet.h"
#include "Core/Math/MathUtils.h"
namespace cg
{
	CLASS_DEFINITION(Player);
	bool Player::Initialize()
	{
		Actor::Initialize();
		auto m_physicsComponent = GetComponent<cg::PhysicsComponent>();
		auto collisionComponent = GetComponent<cg::CollisionComponent>();

		if (collisionComponent) {
			collisionComponent->m_radius = GetComponent<cg::RenderComponent>()->GetRadius() * transform.scale;
		}
		return true;
	}

	/*void Player::OnDestroy()
	{
	}*/

	void Player::Update(float dt)
	{
		Actor::Update(dt);
		float rotate = 0;
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

		transform.rotation += rotate * 0.5f * dt;

		float thrust = 0;
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
		cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(transform.rotation);
		//AddForce(forward * m_speed * thrust);

		transform.position.x = cg::Wrap(transform.position.x, (float)cg::g_renderer.getWidth());
		transform.position.y = cg::Wrap(transform.position.y, (float)cg::g_renderer.getHeight());

		/*auto block = INSTANTIATE(Bullet, "Bullet");
		block->transform = { transform.position, cg::randomf(cg::TwoPi), 1 };
		block->Initialize();*/
		//	m_scene->Add(std::move(block));
		//if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {//}&& m_fireTimer <= 0 && !m_onBlock) {
		//	GetComponent<cg::PhysicsComponent>()->ApplyForce(forward * thrust * speed);
		//}
		m_fireTimer -= dt;
		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0) {
			auto weapon = INSTANTIATE(Bullet, "Bullet");
			weapon->transform = { transform.position + forward * 30, transform.rotation + cg::Deg2Rad(10.0f), 1 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
			m_fireTimer = fireRate;
		}
		//m_onBlock = false;

	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (m_destroyed) return;
		if (other->tag == "Enemy" && dynamic_cast<Enemy*>(other)->m_aliveTime >= 0.5f) {
			cg::g_audioSystem.PlayOneShot("damage", false);
			//m_health -= 8;
			//Particles
			cg::EmitterData data;
			data.burst = true;
			data.burstCount = 40;
			data.spawnRate = 190;
			data.angle = 0;
			data.angleRange = cg::HalfPi;
			data.lifetimeMin = 0.1f;
			data.lifetimeMax = 0.4f;
			data.speedMin = 150;
			data.speedMax = 250;
			data.damping = 0.8f;
			data.color = cg::Color{ 0.5, cg::randomf(0.7f,1.0f), cg::randomf(0.7f,1.0f), 1 };

			cg::Transform transform{ transform.position, 0, 1 };
			auto emitter = std::make_unique<cg::Emitter>(transform, data);
			emitter->lifespan = 0.3f;
			m_scene->Add(std::move(emitter));
		}
		if (other->tag == "Bullet") {
			cg::g_audioSystem.PlayOneShot("damage", false);
			//m_health -= 4;
			//Particles
			cg::EmitterData data;
			data.burst = true;
			data.burstCount = 20;
			data.spawnRate = 90;
			data.angle = 0;
			data.angleRange = cg::HalfPi;
			data.lifetimeMin = 0.1f;
			data.lifetimeMax = 0.2f;
			data.speedMin = 100;
			data.speedMax = 200;
			data.damping = 0.9f;
			data.color = cg::Color{ 0.3f, cg::randomf(0.5f,0.7f), cg::randomf(0.5f,0.7f), 1 };

			cg::Transform transform{ transform.position, 0, 1 };
			auto emitter = std::make_unique<cg::Emitter>(transform, data);
			emitter->lifespan = 0.3f;
			m_scene->Add(std::move(emitter));
		}
		

	}

	
	void Player::Read(const json_t& value) {
		READ_DATA(value, speed);
		READ_DATA(value, fireRate);
	}
}