#include "Player.h"
#include "Input/InputSystem.h"
#include "Block.h"
#include "Framework/Scene.h"
#include "AstroidFighter.h"
#include "Framework/Emitter.h"

#include "Framework/Components/PhysicsComponent.h"

#include "Audio/AudioSystem.h"
#include "Enemy.h"

void Player::Update(float dt)
{
	Actor::Update(dt);
	float rotate = 0;
	if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

	m_transform.rotation += rotate * m_turnRate * dt;

	float thrust = 0;
	if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(m_transform.rotation);
	//AddForce(forward * m_speed * thrust);

	m_transform.position.x = cg::Wrap(m_transform.position.x, (float)cg::g_renderer.getWidth());
	m_transform.position.y = cg::Wrap(m_transform.position.y, (float)cg::g_renderer.getHeight());


	auto physicsComponent = GetComponent<cg::PhysicsComponent>();
	physicsComponent->ApplyForce(forward * thrust * m_speed);

	m_fireTimer -= dt;
	if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0 && !m_onBlock) {
		cg::Transform transform{m_transform.position, cg::randomf(cg::TwoPi), 5};
		std::unique_ptr<Block> block = std::make_unique<Block>(600.0f, transform, cg::random(0, 6), forward.Normalized());
		block->m_tag = "Block";
		block->m_game = m_game;
		m_scene->Add(std::move(block));
		m_fireTimer = m_fireRate;
	}
	m_onBlock = false;
	
}

void Player::OnCollision(Actor* other)
{
	if (m_destroyed) return;
	if (other->m_tag == "Enemy" && dynamic_cast<Enemy*>(other)->m_aliveTime >= 0.5f) {
		cg::g_audioSystem.PlayOneShot("damage", false);
		m_health -= 8;
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

		cg::Transform transform{ m_transform.position, 0, 1 };
		auto emitter = std::make_unique<cg::Emitter>(transform, data);
		emitter->m_lifespan = 0.3f;
		m_scene->Add(std::move(emitter));
	}
	if (other->m_tag == "Bullet") {
		cg::g_audioSystem.PlayOneShot("damage", false);
		m_health -= 4;
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

		cg::Transform transform{ m_transform.position, 0, 1 };
		auto emitter = std::make_unique<cg::Emitter>(transform, data);
		emitter->m_lifespan = 0.3f;
		m_scene->Add(std::move(emitter));
	}
	if (m_health <= 0) {
		m_destroyed = true;
		dynamic_cast<AstroidFighter*>(m_game)->SetState(AstroidFighter::eState::PlayerDeadStart);
	}
	m_onBlock = other->m_tag == "Block";
	
}

void Player::Destroy()
{
	m_destroyed = true;
}
