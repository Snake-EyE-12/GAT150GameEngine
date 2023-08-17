#pragma once
#include "PhysicsComponent.h"
namespace cg
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DECLARATION(EnginePhysicsComponent);

		// Inherited via PhyscisComponent
		virtual void Update(float dt) override;

		virtual void ApplyForce(const Vector2& force) override;

	};
}