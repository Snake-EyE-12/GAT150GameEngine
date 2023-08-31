#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"
namespace cg
{
	class Bullet : public cg::Actor
	{
	public:
		CLASS_DECLARATION(Bullet);
		Bullet() = default;
		Bullet(float speed, const cg::Transform& transform) :
			Actor{ transform },
			m_speed{ speed }
		{
			lifespan = 2.0f;
		}
		bool Initialize() override;
		void OnDestroy() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
	private:
		float m_speed = 0;
		cg::PhysicsComponent* m_physicsComponent = nullptr;
	};
}