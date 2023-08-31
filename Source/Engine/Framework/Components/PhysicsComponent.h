#pragma once
#include "Component.h"
#include "Core/Math/Vector2.h"
namespace cg
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void ApplyForce(const Vector2& force) = 0;
		virtual void ApplyTorque(float torque) = 0;
		virtual void SetVelocity(const Vector2& velocity) { this->m_velocity = velocity; }
	public:
		Vector2 m_velocity;
		Vector2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;
	};
}