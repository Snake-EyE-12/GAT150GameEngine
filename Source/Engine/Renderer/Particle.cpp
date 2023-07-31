#include "Particle.h"
#include "Input/InputSystem.h"
#include "Core/Time.h"
namespace cg
{
	void Particle::Update(float dt)
	{
		m_data.lifetimer += dt;
		if (m_data.lifetimer >= m_data.lifetime)
		{
			m_isActive = false;
			return;
		}
		m_data.prevPosition = m_data.position;
		m_data.position += m_data.velocity * dt;
		m_data.velocity *= std::pow(1.0f - m_data.damping, dt);

		if (cg::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) cg::g_time.SetTimeScale(2.0f);
		else cg::g_time.SetTimeScale(1.0f);
	}
	void Particle::Draw(Renderer& renderer)
	{
		renderer.SetColor(Color::ToInt(m_data.color.r), Color::ToInt(m_data.color.g), Color::ToInt(m_data.color.b), Color::ToInt(m_data.color.a));
		renderer.DrawLine(m_data.position.x, m_data.position.y, m_data.prevPosition.x, m_data.prevPosition.y);
	}
}