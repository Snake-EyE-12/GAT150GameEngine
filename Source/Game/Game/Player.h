#pragma once
#include "Framework/Actor.h"


namespace cg
{
	class Player : public Actor
	{
	public:
		CLASS_DECLARATION(Player);

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;


	private:
		float speed = 0;
		float fireRate = 0;
		float m_fireTimer = 0;

















		/*
		Player(float fireSpeed, float speed, float turnRate, const cg::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_fireRate{ fireSpeed },
			m_turnRate{ turnRate }
		{}
		bool Initialize() override;
		void OnDestroy() override;
		void Update(float dt) override;
		void OnCollision(Actor* other) override;
		void Destroy();
		cg::Text m_text;
	private:
		float m_speed = 0;
		float m_turnRate = 0;
		float m_fireRate = 0;
		float m_fireTimer = 0;
		int m_health = 10;
		bool m_onBlock = false;

		cg::PhysicsComponent* m_physicsComponent = nullptr;
		*/
	};
}