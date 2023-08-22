#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace cg
{
	CLASS_DEFINITION(EnginePhysicsComponent);
	void EnginePhysicsComponent::Update(float dt)
	{

		m_owner->transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void EnginePhysicsComponent::ApplyForce(const Vector2& force)
	{
		m_velocity += force / m_mass;
	}
	void EnginePhysicsComponent::Read(const json_t& value) {

	}
}