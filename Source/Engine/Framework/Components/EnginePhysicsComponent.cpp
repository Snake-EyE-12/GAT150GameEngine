#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

void cg::EnginePhysicsComponent::Update(float dt)
{
	m_owner->m_transform.position += m_velocity * dt;
	m_velocity *= std::pow(1.0f - m_damping, dt);
}

void cg::EnginePhysicsComponent::ApplyForce(const Vector2& force)
{
	m_velocity += force / m_mass;
}
