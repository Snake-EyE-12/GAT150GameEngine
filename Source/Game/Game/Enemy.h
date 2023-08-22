#pragma once
#include "Framework/Actor.h"
#include "Renderer/Model.h"
class Enemy : public cg::Actor
{
public:
	Enemy(float speed, float turnRate, const cg::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;
	
	}
	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	float m_aliveTime = 0;
private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;

};