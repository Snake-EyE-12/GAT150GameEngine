#pragma once
#include "Framework/Actor.h"
#include "Renderer/Text.h"
class Player : public cg::Actor
{
public:
	Player(float fireSpeed, float speed, float turnRate, const cg::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_fireRate{ fireSpeed },
		m_turnRate{ turnRate }
	{}
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
	bool m_onBlock;
};