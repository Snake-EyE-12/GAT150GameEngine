#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"



namespace cg
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy);

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;


	public:
		float speed = 0;
		cg::PhysicsComponent* m_physicsComponent = nullptr;

	};
}
