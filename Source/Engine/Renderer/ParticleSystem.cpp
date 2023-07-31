#include "ParticleSystem.h"
namespace cg
{
	ParticleSystem g_particleSystem(200);
	void ParticleSystem::Update(float dt)
	{
		for (auto& particle : m_particles)
		{
			if (particle.m_isActive) particle.Update(dt);
		}
	}
	void ParticleSystem::Draw(Renderer& renderer)
	{
		for (auto& particle : m_particles)
		{
			if (particle.m_isActive) particle.Draw(renderer);
		}
	}
	Particle* ParticleSystem::GetFreeParticle()
	{
		for (auto& particle : m_particles)
		{
			if (!particle.m_isActive) return &particle;
		}
		return nullptr;
	}
}