#pragma once
#include "Core/Vector2.h"
#include "Renderer/Renderer.h"
#include "Core/Color.h"
namespace cg
{
	struct ParticleData
	{
		Vector2 position;
		Vector2 prevPosition;
		Vector2 velocity;
		float damping = 0;
		Color color;
		float lifetimer = 0;
		float lifetime = 0;
	};

	class Particle
	{
	public:
		Particle() = default;
		void Initialize(const ParticleData& data)
		{
			m_data = data;
			m_isActive = true;
		}
		void Update(float dt);
		void Draw(Renderer& renderer);
		friend class ParticleSystem;
	private:
		ParticleData m_data;
		bool m_isActive = false;
	};
}