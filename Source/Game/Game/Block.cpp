#include "Block.h"
#include "Framework/Emitter.h"
#include "Framework/Scene.h"
#include "AstroidFighter.h"

#include "Audio/AudioSystem.h"

void Block::Update(float dt)
{
	Actor::Update(dt);

	//cg::Vector2 forward = cg::Vector2{ 0, -1 }.Rotate(m_angle);
	m_transform.position += m_forwardV * m_speed * dt;
	//AddForce({ 0.0f, 9.8f * dt * m_gravity });

	//if (m_transform.position.x < 0 || m_transform.position.x >(float)cg::g_renderer.getWidth()) m_destroyed = true;
	m_transform.position.x = cg::Clamp(m_transform.position.x, 0.0f, (float)cg::g_renderer.getWidth());
	m_transform.position.y = cg::Clamp(m_transform.position.y, 0.0f, (float)cg::g_renderer.getHeight());
	if (m_transform.position.y >= (float)cg::g_renderer.getHeight() && !m_placed) {
		Place();
	}
}

void Block::OnCollision(Actor* other)
{
	Block* block = dynamic_cast<Block*>(other);
	if (block && block->m_placed && !m_placed) {
		Place();
	}
	if (m_transform.position.y <= 50 && m_placed && !m_destroyed) {
		dynamic_cast<AstroidFighter*>(m_game)->TetrisMaxHeightReached();
		m_destroyed = true;
	}
	if (other->m_tag == "Laser" && m_transform.position.y <= 30 && !m_placed && !m_destroyed) {
		m_destroyed = true;
		cg::g_audioSystem.PlayOneShot("zap", false);

		//Particles
		cg::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 500;
		data.angle = 0;
		data.angleRange = cg::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMax = 0.7f;
		data.speedMin = 1000;
		data.speedMax = 1250;
		data.damping = 0.2f;
		data.color = cg::Color{ cg::randomf(0.5,1), 0, 0, 1 };

		cg::Transform transform{ m_transform.position, 0, 1 };
		auto emitter = std::make_unique<cg::Emitter>(transform, data);
		emitter->m_lifespan = 0.05f;
		m_scene->Add(std::move(emitter));
	}
}

void Block::Place()
{
	m_speed = 0;
	m_gravity = 0;
	//m_velocity *= 0;
	m_placed = true;
	//std::cout << "Placed" << std::endl;
	if (dynamic_cast<AstroidFighter*>(m_game)->AttemptClearTetris()) m_game->AddPoints(1000);
}

bool Block::Destroy()
{
	if (m_destroyed) return false;
	m_destroyed = true;

	//Particles
	cg::EmitterData data;
	data.burst = true;
	data.burstCount = 10;
	data.spawnRate = 500;
	data.angle = 0;
	data.angleRange = cg::TwoPi;
	data.lifetimeMin = 0.5f;
	data.lifetimeMax = 0.7f;
	data.speedMin = 1000;
	data.speedMax = 1250;
	data.damping = 0.9f;
	//data.color = m_model->GetColor();

	cg::Transform transform{ m_transform.position, 0, 1 };
	auto emitter = std::make_unique<cg::Emitter>(transform, data);
	emitter->m_lifespan = cg::randomf(0.05f, 0.15f);
	m_scene->Add(std::move(emitter));

	return true;
}
